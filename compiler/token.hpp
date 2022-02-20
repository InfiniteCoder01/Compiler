string tokenTypes[] = {
  "operator",
  "prefix",
  "suffix",
  "string",
  "number",
  "char",
  "word",
  "EOF",
};

enum class TokenType {
  OPERATOR,
  PREFIX,
  SUFFIX,
  STRING,
  NUMBER,
  CHAR,
  WORD,
  _EOF
};

struct Token {
  TokenType type;
  string text;

  Token() {
  }

  Token(TokenType t) {
    type = t;
    text = "";
  }

  Token(TokenType t, string v) {
    type = t;
    text = v;
  }

  bool match(TokenType t, string v) {
    return type == t && text == v;
  }
};

inline vector<pair<string, Token>> operators = {
  {"->*", Token(TokenType::OPERATOR, "->*")},
  {"<=>", Token(TokenType::OPERATOR, "<=>")},
  {"<<=", Token(TokenType::OPERATOR, "<<=")},
  {">>=", Token(TokenType::OPERATOR, ">>=")},
  {"...", Token(TokenType::OPERATOR, "...")},
  {"::", Token(TokenType::OPERATOR, "::")},
  {"++", Token(TokenType::OPERATOR, "++")},
  {"--", Token(TokenType::OPERATOR, "--")},
  {"->", Token(TokenType::OPERATOR, "->")},
  {".*", Token(TokenType::OPERATOR, ".*")},
  {"<<", Token(TokenType::OPERATOR, "<<")},
  {">>", Token(TokenType::OPERATOR, ">>")},
  {"<=", Token(TokenType::OPERATOR, "<=")},
  {">=", Token(TokenType::OPERATOR, ">=")},
  {"==", Token(TokenType::OPERATOR, "==")},
  {"!=", Token(TokenType::OPERATOR, "!=")},
  {"&&", Token(TokenType::OPERATOR, "&&")},
  {"||", Token(TokenType::OPERATOR, "||")},
  {"+=", Token(TokenType::OPERATOR, "+=")},
  {"-=", Token(TokenType::OPERATOR, "-=")},
  {"*=", Token(TokenType::OPERATOR, "*=")},
  {"/=", Token(TokenType::OPERATOR, "/=")},
  {"%=", Token(TokenType::OPERATOR, "%=")},
  {"&=", Token(TokenType::OPERATOR, "&=")},
  {"^=", Token(TokenType::OPERATOR, "^=")},
  {"|=", Token(TokenType::OPERATOR, "|=")},
  {"##", Token(TokenType::OPERATOR, "##")},
  {".", Token(TokenType::OPERATOR, ".")},
  {"!", Token(TokenType::OPERATOR, "!")},
  {"~", Token(TokenType::OPERATOR, "~")},
  {"/", Token(TokenType::OPERATOR, "/")},
  {"%", Token(TokenType::OPERATOR, "%")},
  {"+", Token(TokenType::OPERATOR, "+")},
  {"-", Token(TokenType::OPERATOR, "-")},
  {"&", Token(TokenType::OPERATOR, "&")},
  {"^", Token(TokenType::OPERATOR, "^")},
  {"|", Token(TokenType::OPERATOR, "|")},
  {"?", Token(TokenType::OPERATOR, "?")},
  {"<", Token(TokenType::OPERATOR, "<")},
  {">", Token(TokenType::OPERATOR, ">")},
  {"[", Token(TokenType::OPERATOR, "[")},
  {"]", Token(TokenType::OPERATOR, "]")},
  {"{", Token(TokenType::OPERATOR, "{")},
  {"}", Token(TokenType::OPERATOR, "}")},
  {"(", Token(TokenType::OPERATOR, "(")},
  {")", Token(TokenType::OPERATOR, ")")},
  {"*", Token(TokenType::OPERATOR, "*")},
  {",", Token(TokenType::OPERATOR, ",")},
  {":", Token(TokenType::OPERATOR, ":")},
  {"=", Token(TokenType::OPERATOR, "=")},
  {";", Token(TokenType::OPERATOR, ";")},
  {"#", Token(TokenType::OPERATOR, "#")}
};

inline vector<TokenType> replacibles = {
  TokenType::WORD,
  TokenType::PREFIX,
  TokenType::SUFFIX
};