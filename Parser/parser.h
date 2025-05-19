#ifndef PARSER_H
# define PARSER_H

# include "../Lexer/lexer.h"

typedef struct s_redirect
{
    int             type;
    char            *filename;
    struct s_redirect *next;
} t_redirect;

typedef struct s_command
{
    char        **args;
    t_redirect  *redirects;
} t_command;

typedef enum e_cmd_type {
    CMD_SIMPLE,
    CMD_PIPE,
    CMD_AND,
    CMD_OR,
    CMD_SEQUENCE
} t_cmd_type;

typedef struct s_ast
{
    t_cmd_type      type;
    struct s_ast    *left;
    struct s_ast    *right;
    t_command       *command; // CMD_SIMPLE
} t_ast;

t_ast       *parse_tokens_to_ast(t_token *tokens);
void        free_ast(t_ast *node);
void        print_ast_debug(t_ast *node); // Debug
char    **token_list_to_args(t_token *tokens);
#endif
