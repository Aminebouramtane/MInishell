#include "../minishell.h"

void	into_child(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	back_to_parent(int *fd)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	check_dirs(char **dirs_path, int i, char *s, char *command_path)
{
	while (dirs_path[i] != NULL)
	{
		s = ft_strjoin_path(dirs_path[i], command_path);
		if (!access(s, X_OK))
		{
			free(command_path);
			free_split(dirs_path);
			return (s);
		}
		else
			free(s);
		i++;
	}
}

char	*dirs_paths(char *env_path, t_parce_node *parce)
{
	char	**dirs_path;
	char	*s;
	char	*command_path;
	int		i;

	i = 0;
	command_path = NULL;
	s = NULL;
	dirs_path = NULL;
	dirs_path = ft_split(env_path, ':');
	if (!dirs_path)
		return (NULL);
	if (parce && parce->args[0] && ft_strchr(parce->args[0], '/'))
		return (ft_strdup(parce->args[0]));
	if (parce && parce->args[0])
		command_path = ft_strjoin_path("/", parce->args[0]);
	check_dirs(dirs_path, i, s, command_path);
	if (dirs_path)
		ft_free(dirs_path);
	if (command_path)
		free(command_path);
	return (NULL);
}

char	*getpaths(t_parce_node *parce)
{
	char	*env_paths;
	t_env	*temp;

	temp = envi;
	env_paths = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PATH") == 0)
			break ;
		else
			temp = temp->next;
	}
	if (temp == NULL && parce->args[0][0] != '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parce->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (envi)
			envi->exit_status = 127;
		exit(127);
		return (env_paths);
	}
	else if (temp)
		env_paths = ft_strdup(temp->value);
	return (env_paths);
}