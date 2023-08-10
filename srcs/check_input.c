/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:07:04 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/10 06:05:40 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	get_next_quote(char *str, int begin, char quote)
{
	int	i;
	i = begin + 1;
	while(str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-2);
	return (i);
}

bool	check_quotes(char *str)
{
	int	i;
	//int	one_quote;
	//int	two_quote;

	i = 0;
	//one_quote = 0;
	//two_quote = 0;
	while (str[i] && i >= 0)
	{
		if (str[i] == '\'')
		{
			//one_quote += 1;
			i = get_next_quote(str, i, '\'');
			//one_quote += 1;
		}
		else if(str[i] == '"')
		{
			//two_quote += 1;
			i = get_next_quote(str, i, '"');
			//two_quote += 1;
		}
		i++;
	}
	//if ((one_quote > 0 && one_quote % 2 != 0) || (two_quote > 0 && two_quote % 2 != 0) || (i < 0))
	if (i < 0)
		return (false);
	return (true);
}

void	check_input(char *input)
{
	if (input[0] == '\0')
	{
		free(input);
		return ;
	}
	if (check_quotes(input) == false)
	{
		//ft_putstr_fd("unclosed_quotes", STDERR_FILENO);
		printf("FODASSE\n");
		return ;
	}
	
}
