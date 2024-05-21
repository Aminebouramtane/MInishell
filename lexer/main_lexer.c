/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:46:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 11:40:02 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	del(void *str)
{
	free(str);
}

int		lexer(char *str, t_vars *data)
{
	int			i;

	i = 0;
	while ((size_t)i < ft_strlen(str))
	{
		printf("dfdsfsdfsdfsd\n");
		if (!in_delimiters(str[i], "|<>$ \t\'\""))
			fill_string_in_node(str, &i, data, "|<>$ \t\'\"");
		if (str[i] == '\'')
			fill_qoute_in_node(str, &i, data);
		if (str[i] == '\"')
			fill_dqoute_in_node(str, &i, data);
		if (str[i] == '<')
			fill_input_in_node(&i, data);
		if (str[i] == '>')
			fill_output_in_node(&i, data);
		if (str[i] == '$')
			fill_env_in_node(str, &i, data, "|<>$ \t\'\"");
		if (str[i] == '|')
			fill_pipe_in_node(&i, data);
		if (str[i] == '(')
			fill_open_in_node(&i, data);
		if (str[i] == ')')
			fill_close_in_node(&i, data);
		if (in_delimiters(str[i], " \t"))
			fill_white_spaces_in_node(str, &i, data, " \t");
		if (data->flag == 1)
			break;
	}
	while (data->ndata->next)
	{
		printf("cmd >>>%s\n", data->ndata->cmd);
		printf("state >>>%d\n", data->ndata->state);
		printf("type >>>%c\n", data->ndata->type);
		printf("========================\n");
		data->ndata = data->ndata->next;	
	}
	return(1);
}
