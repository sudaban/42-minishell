#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/wait.h>

#include "../minishell.h"
#include "../Libft/libft.h"

char	*get_env_value(const char *key, char **env)
{
	int		i;
	size_t	len;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static void	copy_var_value(char *result, int *j, char *val)
{
	int	m;

	m = 0;
	while (val[m])
	{
		if (val[m] != '\'' && val[m] != '\"')
			result[(*j)++] = val[m];
		m++;
	}
}

char	*expand_variables(const char *input, char **env)
{
	char	*result;
	char	var[256];
	char	*val;
	int		i;
	int		j;
	int		k;

	result = malloc(4096);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			k = 0;
			while (input[i] && (isalnum(input[i]) || input[i] == '_'))
				var[k++] = input[i++];
			var[k] = '\0';
			val = get_env_value(var, env);
			if (val)
				copy_var_value(result, &j, val);
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*find_executable(char *cmd, char **env)
{
	char	*path;
	char	**dirs;
	char	full_path[512];
	char	*ret;
	int		i;

	path = get_env_value("PATH", env);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			ret = ft_strdup(full_path);
			ft_free_double_ptr(dirs);
			return (ret);
		}
		i++;
	}
	ft_free_double_ptr(dirs);
	return (NULL);
}

void	exec_external(char **args, char **env)
{
	int		pid;
	char	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = find_executable(args[0], env);
		if (!cmd_path)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(127);
		}
		execve(cmd_path, args, env);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}
