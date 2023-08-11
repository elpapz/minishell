/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 04:19:38 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/11 02:05:58 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	g_exit_status = 0;


char	*input_prompt()
{
	char	*input;
	char	*temp;
	
	input = readline("Minishell> ");
	temp = ft_strtrim(input, " \t");
	//printf("%s\n", temp);
	//free(temp);
	return (temp);
}

void	running()
{
	char	*line;

	define_signals();
	line = input_prompt();
	// a faltar o control_d!
	//printf("%s\n", line);
	check_input(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	warm_up_shell(envp, info);
	running();


	
}