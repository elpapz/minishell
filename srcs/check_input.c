/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 04:07:04 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/15 06:14:54 by acanelas         ###   ########.fr       */
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
bool	is_there_quotes(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

//check if there is any quote
//if yes, checks if the quotes are closed
//if not closed returns false
bool	check_quotes(char *str)
{
	int	i;
	
	i = 0;
	if (is_there_quotes(str) == false)
		return (true);
	while (str[i] && i >= 0)
	{
		if (str[i] == '\'')
			i = get_next_quote(str, i, '\'');
		else if(str[i] == '"')
			i = get_next_quote(str, i, '"');
		i++;
	}
	//if ((one_quote > 0 && one_quote % 2 != 0) || (two_quote > 0 && two_quote % 2 != 0) || (i < 0))
	if (i < 0)
		return (false);
	return (true);
}
/*
int	get_first_quote(char *str)
{
	int i;

	i = 0;
	while(str[i] && (str[i] != '"' || str[i] != '\''))
		i++;
	return (i);
}
*/

/*
int	get_last_quote(char *str)
{
	int i;
	
	i = ft_strlen(str);
	while(str[i] != '"' || str[i] != '\'')
		i--;
	return (i);
	
}
*/

//removes all the single quotes from the input(str)
//returns the quote_free str malloced
char	*remove_single_quotes(char *str)
{
	//int begin;
	//int	end;
	//char *quotes_free;

	//begin = get_first_quote(str) - 1;
	//end = get_last_quote(str) - 1;
	//quotes_free = ft_substr(str, begin, end - begin);
	int i;
	int j;
	char * quotes_free;

	i = 0;
	j = 0;
	quotes_free = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		while (str[i] == '\'')
			i++;
		quotes_free[j] = str[i];
		i++;
		j++;
	}
	quotes_free[j] = '\0';
	return (quotes_free);
}

//removes all the double quotes from the input(str)
//returns the quote_free str malloced
char	*remove_double_quotes(char *str)
{
	//int begin;
	//int	end;
	//char *quotes_free;

	//begin = get_first_quote(str) - 1;
	//end = get_last_quote(str) - 1;
	//quotes_free = ft_substr(str, begin, end - begin);
	int i;
	int j;
	char *quotes_free;

	i = 0;
	j = 0;
	quotes_free = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		while (str[i] == '"')
			i++;
		quotes_free[j] = str[i];
		i++;
		j++;
	}
	quotes_free[j] = '\0';
	return (quotes_free);
}

bool	invalid_operator(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '<')
			|| (str[i] == '<' && str[i + 1] == '>')
			|| (str[i] == '|' && str[i + 1] == '|'))
				return (true);
		else if (str[i] == '{' || str[i] == '}'
			|| str[i] == '(' || str[i] == ')'
			|| str[i] == '[' || str[i] == ']'
			|| str[i] == ';' || str[i] == '&' || str[i] == '*')
				return (true);
	i++;
	}
	return (false);
}

bool	check_around_quotes(char *str)
{
	
}

bool	wrong_input(char *str)
{
		int	i;

		i = -1;
		if (is_there_quotes(str) == false)
		{
			while (str[++i])
			{
				if ((str[i] == '>' && str[i + 1] == '<')
					|| (str[i] == '<' && str[i + 1] == '>')
					|| (str[i] == '|' && str[i + 1] == '|'))
						return (true);
				else if (str[i] == '{' || str[i] == '}'
					|| str[i] == '(' || str[i] == ')'
					|| str[i] == '[' || str[i] == ']'
					|| str[i] == ';' || str[i] == '&' || str[i] == '*')
						return (true);
			}
		}
		else
			if (check_around_quotes(str))
				return (true);
		return (false);
}

bool	check_input(char *input)
{
	if (check_quotes(input) == false)
	{
		ft_putstr_fd("unclosed quotes, seu cachorro\n", STDERR_FILENO);
		//printf("FODASSE\n");
		return (false);
	}
	if (wrong_input == true)
	{
		ft_putstr_fd("bad input, seu FDP\n", STDERR_FILENO);
		return (false);
	}
	
}
