#define ARENA_IMPLEMENTATION

#include "lexer.h"

int main() {
    lexer lex = {0};

    init_lexer(&lex, "./test.txt");
    

    close_lexer(&lex);
    return 0;
}
