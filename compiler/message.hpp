void message(FILE* stream, string message) {
  fprintf(stream, "%s:%ld:%ld: %s!\n", getFile().filepath.generic_string().c_str(), getFile().line, getFile().column, message.c_str());
}

void error(string error) {
  message(stderr, "Error: " + error);
}