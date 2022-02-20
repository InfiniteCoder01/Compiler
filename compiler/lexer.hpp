#include "token.hpp"

void terminate() {
  fprintf(stderr, "Compilation terminated!\n");
  fflush(stdout);
  fflush(stderr);
  exit(-1);
}

namespace lexer {
#include "fileio.hpp"
#include "message.hpp"

  map<string, string> definitions;
  vector<Path> includePaths;
  bool prevLiteral = false; // TODO: literals

  void begin(string filename) {
    open(filename);
  }

  string getIncludePath(string includePath, bool local) {
    if(local) {
      Path path = fs::absolute(getFile().path).append(includePath);
      if(fs::exists(path)) {
        return path.generic_string();
      }
    }
    for(Path path : includePaths) {
      Path _path = fs::absolute(path).append(includePath);
      if(fs::exists(_path)) {
        return _path.generic_string();
      }
    }
    error("Unknown include path " + includePath);
  }

  bool match(string text) {
    if (getFile().requestBuffer(text.length()) == text) {
      for (int i = 0; i < text.length(); i++) nextChar();
      return true;
    }
    return false;
  }

  string fromCodepoint(unsigned int codepoint) {
    string out;
    if (codepoint <= 0x7f) {
      out.append(1, (char)codepoint);
    } else if (codepoint <= 0x7ff) {
      out.append(1, (char)(0xc0 | ((codepoint >> 6) & 0x1f)));
      out.append(1, (char)(0x80 | (codepoint & 0x3f)));
    } else if (codepoint <= 0xffff) {
      out.append(1, (char)(0xe0 | ((codepoint >> 12) & 0x0f)));
      out.append(1, (char)(0x80 | ((codepoint >> 6) & 0x3f)));
      out.append(1, (char)(0x80 | (codepoint & 0x3f)));
    } else {
      out.append(1, (char)(0xf0 | ((codepoint >> 18) & 0x07)));
      out.append(1, (char)(0x80 | ((codepoint >> 12) & 0x3f)));
      out.append(1, (char)(0x80 | ((codepoint >> 6) & 0x3f)));
      out.append(1, (char)(0x80 | (codepoint & 0x3f)));
    }
    return out;
  }

  string parseBackslash() {
    if (getChar() == 'a') {
      return "\a";
    } else if (getChar() == 'b') {
      return "\b";
    } else if (getChar() == 'f') {
      return "\f";
    } else if (getChar() == 'n') {
      return "\n";
    } else if (getChar() == 'r') {
      return "\r";
    } else if (getChar() == 't') {
      return "\t";
    } else if (getChar() == 'v') {
      return "\v";
    } else if (getChar() == 'x') {
      nextChar();
      char chr = stoul(getFile().requestBuffer(2), nullptr, 16);
      nextChar();
      return string(1, chr);
    } else if (getChar() == 'u') {
      nextChar();
      unsigned int codepoint = stoul(getFile().requestBuffer(4), nullptr, 16);
      for (int i = 0; i < 3; i++)
        nextChar();
      return fromCodepoint(codepoint);
    } else if (getChar() == 'U') {
      nextChar();
      unsigned int codepoint = stoul(getFile().requestBuffer(8), nullptr, 16);
      for (int i = 0; i < 7; i++)
        nextChar();
      return fromCodepoint(codepoint);
    } else if (inRange(getChar(), '0', '7')) {
      string chrTxt = "";
      for (int i = 0; i < 3; i++) {
        chrTxt += getChar();
        if (inRange(getFile().requestBuffer(2)[1], '0', '7')) {
          nextChar();
        } else {
          break;
        }
      }
      return string(1, stoul(chrTxt, nullptr, 8));
    }
    return string(1, getChar());
  }

#include "parsing.hpp"

  void skipComment() {
    while (getChar() != '\n' && getChar() != '\0') {
      if (nextChar() == '\\') {
        nextChar();
      }
    }
  }

  void skipBlockComment() {
    while (!match("*/") && getChar() != '\0') {
      nextChar();
    }
  }

  inline void skipSpaces(bool andLines = false) {
    while(andLines ? isspace(getChar()) : isspacenotln(getChar())) nextChar();
  }

  Token _nextToken() {
    while (true) {
      while (isspace(getChar())) {
        nextChar();
        prevLiteral = false;
      }
      if (match("//")) {
        skipComment();
        continue;
      } else if (match("/*")) {
        skipBlockComment();
        continue;
      }
      break;
    }
    if (getChar() == '\0') {
      return Token(TokenType::_EOF);
    } else if (getChar() == '\"') {
      prevLiteral = true;
      return parseString();
    } else if (getChar() == '\'') {
      prevLiteral = true;
      return parseChar();
    } else if (isidentifierstart(getChar())) {
      Token token = parseWord(prevLiteral);
      prevLiteral = false;
      return token;
    } else if (isdigit(getChar())) {
      prevLiteral = true;
      return parseNumber();
    } else {
      Token token = parseOperator();
      if (token.type == TokenType::_EOF) {
        error("Unknown token starts with " + string(1, getChar()));
      }
      prevLiteral = false;
      return token;
    }
  }

  Token nextToken() { // TODO: define, undef, if, ifdef, ifndef, else, elif, elifdef, elifndef, endif, pragma # ##
    Token token;
    while(true) {
      skipSpaces(true);
      token = _nextToken();
      if(token.match(TokenType::OPERATOR, "#")) {
        skipSpaces();
        token = _nextToken();
        if(token.match(TokenType::WORD, "include")) {
          skipSpaces();
          bool local = getChar() == '\"';
          string includePath;
          if(local) {
            nextChar();
            includePath = readUntil('\"');
          } else if(getChar() == '<') {
            includePath = parsePath();
          } else {
            error("Invailid include path");
          }
          open(getIncludePath(includePath, local));
        } else if(token.match(TokenType::WORD, "line")) {
          skipSpaces();
          if(!isdigit(getChar())) {
            error("Invalid line!");
          }
          getFile().line = stoul(parseNumber().text) - 1;
          skipSpaces();
          if(getChar() != '\n' && getChar() != '\0' && getChar() != '\"') {
            error("Invalid filename in line directive!");
          }
          if(getChar() == '\"') {
            nextChar();
            getFile().path = readUntil('\"');
          }
        } else if(token.match(TokenType::WORD, "error")) {
          skipSpaces();
          if(getChar() == '\"') {
            nextChar();
            error(readUntil('\"'));
          } else {
            error(readUntil('\n'));
          }
        } else {
          error("Invalid preprocessor directive " + token.text);
        }
        continue;
      }
      break;
    }
    return token;
  }

  void end() {
    while (!files.empty()) {
      getFile().close();
      files.pop_back();
    }
  }
}

using lexer::message;
using lexer::error;