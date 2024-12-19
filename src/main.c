#include <stdio.h>

#include "lexer.h"

int main() {
    lexer lex = {0};

    init_lexer(&lex, "./test.txt");
    tokenize(&lex);
    
    // diagnostic prints 
    for (int i = 0; i < lex.token_count; i++) {
        printf("Token %s at %d::%d of %d\n", 
                lex.tokens[i].literal,
                lex.tokens[i].line,
                lex.tokens[i].column,
                lex.tokens[i].type);
    }

    close_lexer(&lex);
    return 0;
}
