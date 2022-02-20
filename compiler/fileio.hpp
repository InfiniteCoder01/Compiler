struct BufferedReader {
  FILE* file;
  Path path;
  size_t line, column;
  string buffer;

  BufferedReader() {
  }

  BufferedReader(string filename) {
    path = filename;
    file = fopen(filename.c_str(), "r");
    line = column = 1;
  }

  string requestBuffer(size_t count) {
    while(buffer.length() < count) {
      int append = count - buffer.length();
      buffer.resize(count);
      fread(buffer.data() + count - append, 1, append, file);
      buffer.erase(remove(buffer.begin(), buffer.end(), '\r'), buffer.end());
    }
    return buffer.substr(0, min(count, buffer.length()));
  }

  char getChar() {
    return requestBuffer(1)[0];
  }

  char nextChar() {
    requestBuffer(2);
    buffer.erase(buffer.begin());
    column++;
    if(getChar() == '\n') {
      column = 1;
      line++;
    }
    return getChar();
  }

  void close() {
    fclose(file);
  }
};

vector<BufferedReader> files;

void open(string filename) {
    files.push_back(BufferedReader(filename));
}

BufferedReader& getFile() {
    return files[files.size() - 1];
}

inline char getChar() {
    return getFile().getChar();
}

inline char nextChar() {
    return getFile().nextChar();
}

inline string requestBuffer(size_t count) {
  return getFile().requestBuffer(count);
}
