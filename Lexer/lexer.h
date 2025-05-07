#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
    T_WORD,
    T_SINGLE_QUOTE,
    T_DOUBLE_QUOTE,
    T_PIPE,
    T_REDIRECT_IN,
    T_REDIRECT_OUT,
    T_APPEND_OUT,
    T_HEREDOC,
    T_ENV_VAR,
    T_EXIT_STATUS,
    T_NEWLINE,
    T_EOF,
    T_OR,
    T_AND,
    T_AMPERSAND
}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}   t_token;

t_token     *lexer(const char *input);
void        free_tokens(t_token *tokens);
void        print_token_debug(t_token *tokens);

#endif