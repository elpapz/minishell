/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:18:55 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:18:55 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_varlst	*env_list(char *name, char *value)
{
	t_varlst	*new;

	new = malloc(sizeof(t_varlst));
	if (!new)
		error(MALLOC, '\0');
	new->var_name = name;
	new->var_value = value;
	new->next = NULL;
	return (new);
}

t_statlst	*create_stat_list(int ac, char **av)
{
	t_statlst	*temp_stat;

	temp_stat = malloc(sizeof(t_statlst));
	if (!temp_stat)
		error(MALLOC, '\0');
	temp_stat->ac = ac;
	temp_stat->av = av;
	temp_stat->next = NULL;
	return (temp_stat);
}

char	**divide_envp(char *str)
{
	char	**env_var;
	int		i;

	i = 0;
	env_var = malloc(sizeof(char *) * 2);
	while (str[i] != '=')
		i++;
	env_var[0] = ft_substr(str, 0, i);
	env_var[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (env_var);
}

t_varlst	*fill_envp_list(char **envp)
{
	t_varlst	*head;
	t_varlst	*temp;
	char		**var_lines;
	int			i;

	var_lines = divide_envp(envp[0]);
	head = env_list(var_lines[0], var_lines[1]);
	i = 0;
	temp = head;
	while (envp[++i])
	{
		free(var_lines);
		var_lines = divide_envp(envp[i]);
		temp->next = env_list(var_lines[0], var_lines[1]);
		temp = temp->next;
	}
	free(var_lines);
	return (head);
}

t_data	*get_data(int ac, char **av, char **envp)
{
	t_data	*temp_data;

	temp_data = (t_data *)malloc(sizeof(t_data));
	if (!temp_data)
		error(MALLOC, '\0');
	temp_data->envp = envp;
	temp_data->stat_head = create_stat_list(ac, av);
	temp_data->var_head = fill_envp_list(envp);
	temp_data->check_out = false;
	temp_data->check_in = false;
	temp_data->tokens_head = NULL;
	return (temp_data);
}
