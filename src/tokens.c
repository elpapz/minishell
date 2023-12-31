/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:16:58 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/12 08:50:40 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern volatile long long g_exit_status;

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

int	count_closed_quotes(char *str)
{
	int	i;
	int n_quotes;
	
	i = 0;
	n_quotes = 0;
	if (is_there_quotes == false)
		return (n_quotes);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = get_next_quote(str, i, '\'');
			n_quotes += 2;
		}
		else if(str[i] == '"')
		{
			i = get_next_quote(str, i, '"');
			n_quotes += 2;
		}
		i++;
	}
	return (n_quotes);
}


/*
char	*cut_quotes_teste(char *input)
{
	int len;
	char *output;
	int output_index;
	bool inside_single_quotes;
	bool inside_double_quotes;
	int i;

	inside_double_quotes = false;
	inside_single_quotes = false;
	output_index = 0;
	len = ft_strlen(input);
	output = malloc(len + 1);
	i = -1;
	while(++i < len)
	{
		if (input[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (input[i] == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else
			output[output_index++] = input[i];
	}
	output[output_index] = '\0';
	return (output);
}


char	*remove_single_quotes(char *str)
{
	int i;
	int j;
	char * quotes_free;

	i = 0;
	j = 0;
	int size = get_unquoted_size(str, '\'');
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
	int size = get_unquoted_size(str, '"');
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
*/

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
	if(!str)
		new_token->command = NULL;
	else
    	new_token->command = ft_strdup(str);
	new_token->type = type;
	new_token->n_quotes = count_closed_quotes(new_token->command);
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
	//free(str);
	return (0);
}

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

char	*get_path(char *input, int *i)
{
	int		len;
	int		i_temp;
	char	*temp;

	i_temp = *i;
	temp = malloc(sizeof(char) * (i_temp - *i + 1));
	len = 0;
	(*i)++;
	while (input[i_temp] && isalnum(input[i_temp]))
		i_temp++;
	while (input[*i] && isalnum(input[*i]))
	{
		temp[len] = input[*i];
		(*i)++;
		len++;
	}
	temp[len] = '\0';
	return (temp);
}

int	get_len_path(char *input, t_data *data)
{
	int		len;
	int		i;
	char	*temp_path;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path, data);
			len += ft_strlen(temp_path);
			free(temp_path);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
}


char	*get_path_input(char *input, t_data *data)
{
    int		i;
	int		len;
	int		i_temp;
	char	*temp_path;
	char	*temp_input;

	i = 0;
	len = get_len_path(input, data);
	temp_input = malloc(sizeof(char) * len);
	len = 0;
	while (input[i])
	{
		if(input[i] == '$' && input[i+1] == '?'
			&& input[0] != '\'')
			{
				char *temp_int;
				int i_int_temp = 0;

				temp_int = ft_itoa(g_exit_status);
				while(temp_int[i_int_temp])
				{
					temp_input[len] = temp_int[i_int_temp];
					i_int_temp++;
					len++;
				}
				i += 2;
				free(temp_int);
			}
		else if(input[i] == '$' && !ft_isalnum(input[i+1]))
		{
			temp_input[len++] = '$';
			i++;
		}
		else if (input[i] == '$' && input[0] != '\'')
		{
			temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path, data);
			i_temp = 0;
			while (temp_path[i_temp])
			{
				temp_input[len] = temp_path[i_temp];
				i_temp++;
				len++;
			}
			free(temp_path);
		}
		else
		{
			temp_input[len] = input[i];
			len++;
			i++;
		}
	}
	temp_input[len] = 0;
	//printf("temp_input %s\n", temp_input);
	return (temp_input);
}

/*
void	remove_head_quotes(t_tokens *head,t_data *data)
{
	if (is_there_quotes(head->command))
	{
		if (head->command[0] == '\'')
			head->command = remove_single_quotes(head->command);
		else if (head->command[0] == '"')
		{
			head->command = get_path_input(head->command,data);
			head->command = remove_double_quotes(head->command);
		}
	}
	else
		return ;
}

void	remove_quotes(t_tokens *head,t_data *data)
{
	while (head != NULL)
	{
		if(head->command[0] != '\'')
			head->command = get_path_input(head->command,data);
		//mesmo se nao tiver quotes a funcao funciona , se caso n tiver quotes
		//ele simplesmente nao muda nada na string
		head->command = cut_quotes_teste(head->command);
		head = head->next;
	}
}
*/

char	*deal_with_quotes(char *str, t_tokens *token)
{
	int i;
	int j;
	char	quote_type;
	char *quotes_free;

	i = -1;
	j = 0;
	int size = ft_strlen(str) - token->n_quotes; 
	printf("size of unquoted--> %d\n", size);
	quotes_free = malloc(sizeof(char) * ft_strlen(str) - token->n_quotes + 1);
	ft_printf("before deal --> %s\n", str);
	while (str[++i])
	{
		while (str[i] != '\'' && str[i] != '"')
			quotes_free[j++] = str[i++];
		quote_type = str[i];
		while (str[i] == quote_type)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] != quote_type)
			quotes_free[j++] = str[i++];
	}
	free(str);
	quotes_free[j] = '\0';
	printf("after deal --> %s\n", quotes_free); // tem 4 comentarios, ou seja é igual a 25 linhas(norm ok)
	return (quotes_free);
}

void	take_away_quotes(t_tokens *head, t_data *data)
{
		while (head != NULL)
		{
			if (is_there_quotes(head->command))
			{
				if(head->command[0] != '\'')
					head->command = get_path_input(head->command,data);
				head->command = deal_with_quotes(head->command, head);
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
		i++;
	}
	take_away_quotes(data->tokens_head, data);
	return (data->tokens_head);
}
/*
void remove_node(t_tokens **head, t_tokens *node_to_remove)
{
    if (*head == NULL || node_to_remove == NULL)
        return; // Verificar se a lista ou o nó para remover são nulos

    if (*head == node_to_remove)
    {
        // Se o nó a ser removido é o primeiro nó da lista
        *head = (*head)->next; // Atualize o ponteiro da cabeça para o próximo nó
        free(node_to_remove);  // Libere a memória do nó removido
        return;
    }

    // Encontre o nó anterior ao nó a ser removido
    t_tokens *prev = *head;
    while (prev->next != NULL && prev->next != node_to_remove)
    {
        prev = prev->next;
    }

    // Se o nó a ser removido foi encontrado, ajuste os ponteiros
    if (prev->next == node_to_remove)
    {
        prev->next = node_to_remove->next; // Atualize o ponteiro "next" do nó anterior
        free(node_to_remove);              // Libere a memória do nó removido
    }
}

void get_type_input(t_tokens *temp)
{
	t_type type_temp;
	int len_string;

	while(temp)
	{
		type_temp = NORMAL;
		len_string = ft_strlen(temp->command);
		if(temp->command[0] == '<' && temp->command[1] == '<' && len_string == 2)
			temp->next->type = RDR_RD_IN;
		else if(temp->command[0] == '<' && len_string == 1)
			temp->next->type = RDR_IN;
		else if(temp->command[0] == '>' && len_string == 1)
			temp->next->type = RDR_OUT;
		else if(temp->command[0] == '>' && temp->command[1] == '>' && len_string == 2)
			temp->next->type = RDR_AP_OUT;
		else if(temp->command[0] == '|' && len_string == 1)
			temp->type = PIPE;
		temp = temp->next;
	}
}
*/
/*
t_tokens	*get_tokens(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while(str[i] == ' ' || str[i] == '\t')
			i++;
		// if (is_there_token(str[i]) != NORMAL)
		// 	i = get_new_token(str, i, &data->tokens_head);
		// else
		i = get_word_until(str, i, &data->tokens_head);
		if (i < 0)
			return (NULL);
		else if (str[i] == '\0')
			break ;
		//remove_head_quotes(data->tokens_head); //remove the quotes only from the first token(command)
		i++;
	}
	remove_quotes(data->tokens_head,data); //remove the quotes from all the tokens(commands)
	get_type_input(data->tokens_head);
	t_tokens *temp = NULL;
	t_tokens *temp2;

	temp2 = data->tokens_head;
	while(temp2->next)
	{
		if(temp2->next->type == NORMAL || temp2->next->type == PIPE)
			add_token(&temp,temp2->command,temp2->type);
		temp2 = temp2->next;
	}
	add_token(&temp,temp2->command,temp2->type);
	return (temp);
}
*/


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

