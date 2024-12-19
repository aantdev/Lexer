#ifndef LEXER_H 
#define LEXER_H

#define MAX_TOKENS 100

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_EOF
} t_type;

typedef struct {
    t_type type;
    char* literal;
    int line;
    int column;
} token;

typedef struct {
    char* src;
    int length;
    int current;
    int line;
    int column;
    
    int token_limit;
    int token_count;
    token* tokens;
} lexer;

int init_lexer(lexer* lex, char* path);
void close_lexer(lexer* lex);

int add_token(lexer* lex, int start, int length, t_type type);
void tokenize(lexer* lex);

#endif
