bool isletterordigit(int c) {
  return isalpha(c) != 0 || isdigit(c);
}

bool isidentifierstart(int c) {
  return isalpha(c) != 0 || c == '_';
}

bool isidentifierpart(int c) {
  return isletterordigit(c) || c == '_';
}

bool isspacenotln(int c) {
  return isspace(c) && c != '\n';
}

char tochar(int c) {
  if(c == EOF) {
    return '\0';
  }
  return c;
}