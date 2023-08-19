#include "../include/minishell.h"

int len_strings(char **cmd)
{
	int i;

	i = 0;
	while(cmd[i])
		i++;
	return i;
}

void print_string(char **str)
{
	int i;

	i = 0;
	while(str[i])
		ft_printf("%s\n",str[i++]);
}

char	*remove_single_quotes(char *str)
{
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
