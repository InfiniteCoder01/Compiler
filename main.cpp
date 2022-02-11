#include "init.hpp"
#include "character.hpp"
// #include "compiler/preprocessor.hpp"
#include "compiler/lexer.hpp"

int main() {
    string filename = "test.hpp";
    // string outfile = "test.exe";
    lexer::includePaths.push_back("/mnt/c/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/lib/gcc/x86_64-w64-mingw32/9.2.0/include/c++/");
    lexer::includePaths.push_back("/mnt/c/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/x86_64-w64-mingw32/include/");
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