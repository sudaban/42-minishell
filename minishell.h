#ifndef MINISHELL_H
# define MINISHELL_H
#include <stddef.h>

typedef struct s_shell
{
	char	**env;
}	t_shell;

char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);

#endif
