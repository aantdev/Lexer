#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "utils.h"

char* temp[] = {"Keyword", "Number", "Symbol", "EOF"};
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage:\n./lex <input.txt>\n");
        exit(EXIT_FAILURE);
    }
    
    lexer lex = {0};
    init_lexer(&lex, argv[argc-1]);
    error_handle(&lex);

    tokenize(&lex);
    // diagnostic prints 
    for (int i = 0; i < lex.token_count; i++) {
        printf("Token %s at %d::%d of type %s\n", 
                lex.tokens[i].literal,
                lex.tokens[i].line,
                lex.tokens[i].column,
                temp[lex.tokens[i].type]);
    }
    
    printf("%d, %d\n", lex.token_count, lex.token_limit);
    error_handle(&lex);
    return 0;
}
