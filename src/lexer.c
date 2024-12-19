#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
    lexer->token_limit = MAX_TOKENS;

    // check if file_to_string succeeded first.
    if (lexer->src == NULL)
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

int add_token(lexer *lex, int start, int length, t_type type) {
    lex->tokens[lex->token_count].literal = malloc(length);
    if (lex->tokens[lex->token_count].literal == NULL)
        return 1;
    
    memcpy(lex->tokens[lex->token_count].literal, lex->src + start, length-1); 
    lex->tokens[lex->token_count].literal[length-1] = '\0';
    
    lex->tokens[lex->token_count].line = lex->line;
    lex->tokens[lex->token_count].column = lex->column;
    lex->tokens[lex->token_count].type = type;
    
    lex->token_count++;
    if (lex->token_count > lex->token_limit){
        lex->token_limit *= 2;
        lex->tokens = realloc(lex->tokens, sizeof(token) * lex->token_limit);
        if (lex->tokens == NULL)
            return 1;
    }

    return 0;
}

void tokenize(lexer* lex) {
    while (lex->current < lex->length) {
        char c = lex->src[lex->current]; 
        const char c_n = lex->src[lex->current+1]; 

        const int whitespace = (c == ' ');
        const int newline = (c == '\n');
        const int symbol = ( c == ';' ) || ( c == '=' ) || 
                           ( c == ')' ) || ( c == '(' ) || 
                           ( c == '}' ) || ( c == '{' ) ||
                           ( c == ',' ) || ( c == ':' ) ;
        const int comment = (c == '/') && (c_n == '/');
        // Newline or whitespace, skip
        if (whitespace) {
            lex->current++;
            lex->column++;
            continue;
        }

        if (newline) {
            lex->current++;
            lex->column = 0;
            lex->line++;
        }

        // Caught comment, skip.
        if (comment) {
            while (lex->src[lex->current] != '\n') {
                lex->current++;
            }
            lex->column = 0;
            lex->line++;
            continue;
        }

        // Caught symbol. store as token.
        // TOKEN_SYMBOL
        if (symbol) {
            // exactly two chars. [0] = 'char', [1] = '\0'
            int length = 2;
            int start = lex->current;
            add_token(lex, start, length, TOKEN_SYMBOL);

            lex->current++;
            lex->column++;
            continue;
        }
        
        // Caught character, start reading.
        // then identify token type
        // then store as token
        if (isalpha(c)) {
            int start = lex->current;
            while (isalpha(c)) {
                lex->current++;
                lex->column++;

                c = lex->src[lex->current];
            }
            int length = (lex->current - start) + 1;
            
            add_token(lex, start, length, TOKEN_KEYWORD);
            continue;
        }
    
        // caught digit
        // store as TOKEN_NUMBER
        if (isdigit(c)) {
            int start = lex->current;
            while (isdigit(c)) {
                lex->current++;
                lex->column++;

                c = lex->src[lex->current];
            }
            int length = (lex->current - start) + 1;
            
            add_token(lex, start, length, TOKEN_KEYWORD);
            continue;
        }

    } 
}
