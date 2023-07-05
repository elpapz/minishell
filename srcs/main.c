/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 04:19:38 by acanelas          #+#    #+#             */
/*   Updated: 2023/07/05 04:03:34 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	g_exit_status = 0;


void	work_bitch(t_info *info)
{
	char	*input;

	define_signals();
	input = readline("Minishell> ");
	if (input == NULL)
	{
		return (0);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*line;

	(void)argc;
	(void)argv;
	warm_up_shell(envp, &info);

	
}