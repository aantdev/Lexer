#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"
#include "utils.h"

int init_lexer(lexer* lexer, char* path) {
    int success = 0;

    lexer->src = ftostr(path);
    lexer->current = 0;
    lexer->line = 0;
    lexer->column = 0;
    lexer->token_count = 0;

    // check if file_to_string succeeded first.
    if (lexer->src != NULL)
        return 1;

    lexer->length = strlen(lexer->src);
    
    // if all is ok, then alloc some tokens
    lexer->tokens = malloc(sizeof(token) * MAX_TOKENS);
    if (lexer->tokens == NULL)
        return 1;

    return success;
} 

void close_lexer(lexer *lex) {
    free(lex->tokens);
    free(lex->src);

    lex->src = NULL;
    lex->tokens = NULL;
}

void tokenize(lexer* lex) {
    while (lex->current < lex->length) {
        const char c = lex->src[lex->current]; 
        const char c_n = lex->src[lex->current+1]; 

        const int white_or_new = (c == ' ') || (c == '\n');
        const int symbol = ( c == ';' ) || ( c == '=' ) || 
                           ( c == ')' ) || ( c == '(' ) || 
                           ( c == '}' ) || ( c == '{' ) ||
                           ( c == ',' ) || ( c == ':' ) ;
        const int comment = c == '/' && c_n == '/';
        
        // Newline or whitespace, skip
        if (white_or_new) {

        }

        // Caught comment, skip.
        if (comment) {
            
        }

        // Caught symbol. store as token.
        if (symbol) {

        }
        
        // Caught character, start reading.
        // then identify token type
        // then store as token
        if (isalpha(c)) {
            
        }
    
        // caught digit
        // store as TOKEN_NUMBER
        if (isdigit(c)) {

        }
    } 
}
