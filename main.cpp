#include "init.hpp"
#include "character.hpp"
// #include "compiler/preprocessor.hpp"
#include "compiler/lexer.hpp"

int main() {
    string filename = "test.hpp";
    lexer::includePaths.push_back("/mnt/d/Dev/C++/Compilation/STL/C/include");
    lexer::includePaths.push_back("/mnt/d/Dev/C++/Compilation/STL/C++/include");
    lexer::definitions["true"] = "1";
    lexer::definitions["false"] = "0";
    lexer::begin(filename);
    while (true) {
        Token t = lexer::nextToken();
        if (t.type == TokenType::_EOF) {
            break;
        }
        printf("%s %s\n", tokenTypes[(int)t.type].c_str(), t.text.c_str());
    }
    lexer::end();
    return 0;
}