/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:07:04 by acanelas          #+#    #+#             */
/*   Updated: 2023/07/13 03:03:42 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


bool	check_quotes(char *str)
{
	int	i;
	int	is_found;
	char	quote;

	i = 0;
	is_found = 0;
	quote = 0;

	while (str[i] && quote == '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			is_found = 1;
		}
		i++;
	}
	while (str[i] && is_found != 2)
	{
		if (str[i] && str[i] == quote)
		{
			quote = 0;
			is_found = 2;
		}
		i++;
	}
	if (is_found == 1)
		return (false);
	else if (is_found == 2)
		return (true);
	else
		return (true);
}

void	check_input(char *input, t_info *info)
{
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	if (check_quotes(input) == false)
	{
		ft_putstr_fd("unclosed_quotes", STDERR_FILENO);
		return (0);
	}
	
}