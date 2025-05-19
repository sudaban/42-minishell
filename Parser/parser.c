#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

static t_token_type get_operator_type(t_token *tok)
{
    if (!tok) return -1;
    if (tok->type == T_PIPE) return 1;
    if (tok->type == T_AND) return 2;
    if (tok->type == T_OR) return 3;
    // ; char not implemented
    return -1;
}

static t_ast *create_ast_node(t_cmd_type type, t_ast *left, t_ast *right)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = type;
    node->left = left;
    node->right = right;
    node->command = NULL;
    return node;
}

static t_ast *parse_simple_command(t_token *tokens)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = token_list_to_args(tokens);
    cmd->redirects = NULL;

    t_ast *node = malloc(sizeof(t_ast));
    node->type = CMD_SIMPLE;
    node->left = NULL;
    node->right = NULL;
    node->command = cmd;
    return node;
}

t_ast *parse_tokens_to_ast(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        int op_type = get_operator_type(current);
        if (op_type != -1)
        {
            current->value = NULL;
            current->type = T_EOF;

            t_ast *left = parse_tokens_to_ast(tokens);
            t_ast *right = parse_tokens_to_ast(current->next);
            return create_ast_node(op_type, left, right);
        }
        current = current->next;
    }

    return parse_simple_command(tokens);
}

void print_ast_debug(t_ast *node)
{
    if (!node) return;
    if (node->type == CMD_SIMPLE)
    {
        printf("CMD_SIMPLE: ");
        for (int i = 0; node->command->args[i]; i++)
            printf("%s ", node->command->args[i]);
        printf("\n");
    }
    else
    {
        const char *type_str[] = {"CMD_SIMPLE", "PIPE", "AND", "OR", "SEQ"};
        printf("NODE: %s\n", type_str[node->type]);
        print_ast_debug(node->left);
        print_ast_debug(node->right);
    }
}

#include "../Libft/libft.h"
#include <stdlib.h>

char **token_list_to_args(t_token *tokens)
{
    int count = 0;
    t_token *tmp = tokens;

    while (tmp && tmp->type != T_PIPE && tmp->type != T_AND && tmp->type != T_OR)
    {
        if (tmp->type == T_WORD || tmp->type == T_DOUBLE_QUOTE || tmp->type == T_SINGLE_QUOTE)
            count++;
        tmp = tmp->next;
    }

    char **args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return NULL;

    int i = 0;
    while (tokens && tokens->type != T_PIPE && tokens->type != T_AND && tokens->type != T_OR)
    {
        if (tokens->type == T_WORD || tokens->type == T_DOUBLE_QUOTE || tokens->type == T_SINGLE_QUOTE)
            args[i++] = ft_strdup(tokens->value);
        tokens = tokens->next;
    }
    args[i] = NULL;
    return args;
}
