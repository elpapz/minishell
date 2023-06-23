/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 04:19:38 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/19 04:34:46 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*line;

	if (argc != 1 && argv[1])
		exit(EXIT_FAILURE);
	
}