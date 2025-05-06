#ifndef EXPORT_H
# define EXPORT_H

# include "../../minishell.h"

int		builtin_export(char **args, t_shell *shell);
int		is_valid_key(char *arg);
int		replace_env(char *new_entry, char ***env);
char	**append_env(char *new_entry, char **env);
char	*str_dup(const char *src);

#endif
