#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
int	print_env(char **env)
{
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (i);
}

int  main(char **av, int ac, char **envp)
{
	(void) av;
	(void) ac;
	int i = print_env(envp);
	printf("\n\n\n\n%i\n", i);
}
*/

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
	quotes_free = malloc(sizeof(char) * strlen(str) + 1);
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

int main(){
	char *str = remove_single_quotes("..  ola'adeus'");
	printf("%s\n", str);
}
