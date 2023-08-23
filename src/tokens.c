#include "../include/minishell.h"

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

int add_token(t_tokens **head, char *str,t_type type)
{
    t_tokens *new_token = malloc(sizeof(t_tokens));
	t_tokens *temp;
    if (!new_token)
        return (-1);
    //new_token->command = ft_strdup(str); //tambem dá com ft_strdup
	new_token->command = str;
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

t_tokens	*get_tokens(t_data *data, char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		while(str[i] == ' ' || str[i] == '\t')
			i++;
		if (is_there_token(str[i]) != NORMAL)
			i = get_new_token(str, i, &data->tokens_head);
		else
			i = get_word_until(str, i, &data->tokens_head);
		if (i < 0)
			return (NULL);
		i++;
	}
	return (data->tokens_head);
}

/*
t_tokens *tokens_input(char *input,t_data *data)
{
	t_tokens *temp;
	t_type type;
	char **command;
	int i;

	i = 0;
	command = ft_split(input,' ');
	temp = NULL;
	type = NORMAL;
	while(command[i])
	{
		if(!ft_strchr(command[i],'>')
			&& !ft_strchr(command[i],'<'))
		{
			if(ft_strchr(command[i],'|'))
			{
				add_token(&temp,command[i],PIPE);
				type = NORMAL;
			}
			else
				add_token(&temp,command[i],type);
			if(type == RDR_RD_IN)
				type = NORMAL;
			i++;
		}
		else
		{
			if(!ft_strncmp(command[i],">>",3))
				type = RDR_AP_OUT;
			else if(!ft_strncmp(command[i],"<<",3))
				type = RDR_RD_IN;
			else if(ft_strchr(command[i],'>'))
				type = RDR_OUT;
			else if(ft_strchr(command[i],'<'))
				type = RDR_IN;
			if(type == RDR_AP_OUT
				|| type == RDR_OUT)
				data->check_out = true;
			if(type == RDR_RD_IN
			|| type == RDR_IN)
				data->check_in = true;
			i++;
		}
	}
	//free_strings(command);
	free(input);
	return temp;
}
*/
