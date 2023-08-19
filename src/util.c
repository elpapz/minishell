#include "../include/minishell.h"

char *ft_mllstrcpy(char *str)
{
	int i;
	int len;
	char *temp;

	i = 0;
	len = ft_strlen(str);
	temp = malloc(sizeof(char) * (len + 1));
	while(str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return temp;
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
