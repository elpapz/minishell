/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 04:19:38 by acanelas          #+#    #+#             */
/*   Updated: 2023/07/13 02:12:23 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	g_exit_status = 0;


char	*input_prompt(t_info *info)
{
	char	*input;

	input = readline("Minishell> ");
	if (input == NULL)
	{
		free(input);
		return (0);
	}
	char	*temp;
	
	temp = ft_strtrim(input, " \t");
	free(temp);
	return (temp);
}

void	running(t_info *info)
{
	char	*line;

	define_signals();
	line = input_prompt(&info);
	// a faltar o control_d!
	check_input(line, &info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	(void)argc;
	(void)argv;
	warm_up_shell(envp, &info);
	while (1)
	{
		running(&info);
	}

	
}