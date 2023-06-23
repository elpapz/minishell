/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warm_up_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 04:21:38 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/23 05:37:35 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//got to init the INFO STRUCT and the ENVP and the OLDPWD

char	**divide_envp(char *str)
{
	char	**var;
	int	i;

	i = 0;
	var = malloc(sizeof(char *) * 2);
	while (str[i] != '=')
		i++;
	var[0] = ft_substr(str, 0, i);
	var[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (var);
	
}

void	fill_envp_list(char **envp, t_info *info)
{
	t_varb	*head;
	t_varb	*temp;
	char	**var_line;
	int	i;

	var_line = divide_envp(envp[0]);
	head = create_var_list(var_line[0], var_line[1]);
	i = 0;
	temp = head;
	while (envp[++i])
	{
		free(var_line);
		var_line = divide_envp(envp[i]);
		temp->next = create_var_list(var_line[0], var_line[1]);
		temp = temp->next;
	}
	free (var_line);
	return (head);
}


void	warm_up_shell(char **envp, t_info *info)
{
	info->envp = envp;
	fill_envp_list(envp, info);
}