#include "../minishell.h"


void	ft_pwd(t_env *envi)
{
	t_env *temp;
	int	i;
	char *path;

	temp = envi;
	i = 0;
	while (temp)
	{
		path = ft_strstr(temp->env_var, "PWD=");
		if (path != NULL)
			break ;
		temp = temp->next;
	}
	path += 4;
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}

