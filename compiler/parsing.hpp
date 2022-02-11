using namespace lexer;

Token parseWord(bool suffix) {
  string word = "";
  do {
    word += getChar();
  } while (isidentifierpart(nextChar()));
  if (getChar() == '\'' || getChar() == '\"') {
    return Token(TokenType::PREFIX, word);
  } else if (suffix) {
    return Token(TokenType::SUFFIX, word);
  }
  return Token(TokenType::WORD, word);
}

Token parseOperator() {
  for (pair<string, Token> op : operators) {
    if (match(op.first)) {
      return op.second;
    }
  }
  return Token(TokenType::_EOF);
}

Token parseNumber() { // TODO: better number parser
/*
1.0
1e-1; 1 * 10^-1
0.1e-1; 0.1 * 10^-1
0x2p-1; 0x2 * 2^-1
0xf.fp-1; (0xf + 0xf / 16) * 2^-1
*/
// 0x2p-1; 0x2 * 2^-1
  bool hex = match("0x") || match("0X");
  string n = hex ? "0x" : "";
  do {
    n += getChar();
  } while (string(hex ? "0123456789ABCDEFabcdef'" : "0123456789'.").find(nextChar()) != string::npos);
  return Token(TokenType::NUMBER, n);
}

Token parseString() {
  string str = "";
  while (nextChar() != '\"' && getChar() != '\n' && getChar() != '\0') {
    if (getChar() == '\\') {
      nextChar();
      str += parseBackslash();
    } else {
      str += getChar();
    }
  }
  if (getChar() != '\"') {
    error("Missing terminating \" character");
  }
  nextChar();
  return Token(TokenType::STRING, str);
}

Token parseChar() { // TODO: too long characters (show error)
  string chr = "";
  while (nextChar() != '\'' && getChar() != '\n' && getChar() != '\0') {
    if (getChar() == '\\') {
      nextChar();
      chr += parseBackslash();
    } else {
      chr += getChar();
    }
  }
  if (getChar() != '\'') {
    error("Missing terminating \' character");
  }
  nextChar();
  return Token(TokenType::CHAR, chr);
}