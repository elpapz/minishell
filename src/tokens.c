/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:16:58 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/08 06:26:48 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_unquoted_size(char *str)
{
	int	start;
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		while (str[i] == '"')
			i++;
		start = i;
		while (str[i] != '"')
			i++;
		return (i - start);
	}
	else if (str[i] == '\'')
	{
		while (str[i] == '\'')
			i++;
		start = i;
		while (str[i] != '\'')
			i++;
		return (i - start);
	}
}

char	*remove_single_quotes(char *str)
{
	int i;
	int j;
	char * quotes_free;

	i = 0;
	j = 0;
	int size = get_unquoted_size(str);
	//printf("%d\n", size);
	quotes_free = malloc(sizeof(char) * size + 1);
	while (str[i])
	{
		while (str[i] == '\'')
			i++;
		if (str[i] == '\0')
			break ;
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
	int i;
	int j;
	char *quotes_free;

	i = 0;
	j = 0;
	int size = get_unquoted_size(str);
	//printf("%d\n", size);
	quotes_free = malloc(sizeof(char) * size + 1);
	while (str[i])
	{
		while (str[i] == '"')
			i++;
		if (str[i] == '\0')
			break ;
		quotes_free[j] = str[i];
		i++;
		j++;
	}
	quotes_free[j] = '\0';
	return (quotes_free);
}

t_type	is_there_token(char c)
{
	if (c == '<')
		return (RDR_IN);
	if (c == '>')
		return (RDR_OUT);
	if (c == '|')
		return (PIPE);
	return (NORMAL);
}
/*
void	add_token(t_tokens **head, char *str, t_type type)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->command = ft_mllstrcpy(str);
	new_token->type = type;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	printf("tokens ->%s\n", new_token->command);
}
*/

int add_token(t_tokens **head, char *str,t_type type)
{
    t_tokens *new_token;
	t_tokens *temp;

	new_token = malloc(sizeof(t_tokens));
    if (!new_token)
        return (-1);
    new_token->command = ft_strdup(str); //tambem dá com ft_strdup
	new_token->type = type;
    new_token->next = NULL;
    if (!*head)
        *head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	printf("token ->%s\n", new_token->command);
	return (0);
}
//RDR_RD_IN
int	get_new_token(char *str, int i, t_tokens **head)
{
	int checker;

	if (str[i] == '<' && str[i + 1] == '<')
	{
		checker = add_token(head, NULL, RDR_RD_IN);
		i += 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		checker = add_token(head, NULL, RDR_AP_OUT);
		i += 1;
	}
	else if (str[i] == '<')
		checker = add_token(head, NULL, RDR_IN);
	else if (str[i] == '>')
		checker = add_token(head, NULL, RDR_OUT);
	else if (str[i] == '|')
		checker = add_token(head, NULL, PIPE);
	if (checker == (-1))
		return (checker);
	return (i);
}

int	get_word_until(char *str, int i, t_tokens **head)
{
	int	begin;
	int	checker;

	begin = i;
	while (str[i])
	{
		if (is_there_token(str[i] != NORMAL) || str[i] == ' ' || str[i] == '\t')
			break ;
		if (str[i] == '\'')
			i = get_next_quote(str, i, '\'');
		else if (str[i] == '"')
			i = get_next_quote(str, i, '"');
		i++;
	}
	checker = add_token(head, ft_substr(str, begin, i - begin), NORMAL);
	if (checker == (-1))
		return (checker);
	return (i);
}


void	remove_head_quotes(t_tokens *head)
{
	//int	i;

	//i = 0;
	if (is_there_quotes(head->command))
	{
		if (head->command[0] == '\'')
			head->command = remove_single_quotes(head->command);
		else if (head->command[0] == '"')
			head->command = remove_double_quotes(head->command);
	}
	else
		return ;
}


void	remove_quotes(t_tokens *head)
{
	//int i = 0;
	while (head != NULL)
	{
		if (is_there_quotes(head->command))
		{
			if (head->command[0] == '\'')
			head->command = remove_single_quotes(head->command);
		else if (head->command[0] == '"')
			head->command = remove_double_quotes(head->command);
		}
		head = head->next;
	}
}

t_tokens	*get_tokens(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while(str[i] == ' ' || str[i] == '\t')
			i++;
		if (is_there_token(str[i]) != NORMAL)
			i = get_new_token(str, i, &data->tokens_head);
		else
			i = get_word_until(str, i, &data->tokens_head);
		if (i < 0)
			return (NULL);
		else if (str[i] == '\0')
			break ;
		//remove_head_quotes(data->tokens_head); //remove the quotes only from the first token(command)
		i++;
	}
	remove_quotes(data->tokens_head); //remove the quotes from all the tokens(commands)
	return (data->tokens_head);
}



/*
void	add_token(t_tokens **head, char *str, t_type type)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->command = ft_mllstrcpy(str);
	new_token->type = type;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	printf("tokens ->%s\n", new_token->command);
}

t_tokens	*tokens_input(char **command, t_data *data)
{
	t_tokens	*temp;
	t_type		type;
	char		**split_pipe;
	int			i;

	i = 0;
	temp = NULL;
	type = NORMAL;
	while (command[i])
	{
		if (!ft_strchr(command[i], '>')
			&& !ft_strchr(command[i], '<'))
		{
			if (ft_strchr(command[i], '|'))
			{
				add_token(&temp, "|", PIPE);
				type = NORMAL;
			}
			else
				add_token(&temp, command[i], type);
			type = NORMAL;
			i++;
		}
		else
		{
			if (!ft_strncmp(command[i], ">>", 3))
				type = RDR_AP_OUT;
			else if (!ft_strncmp(command[i], "<<", 3))
				type = RDR_RD_IN;
			else if (ft_strchr(command[i], '>'))
				type = RDR_OUT;
			else if (ft_strchr(command[i], '<'))
				type = RDR_IN;
			i++;
		}
	}
	free_strings(command);
	return (temp);
}
*/

