#include <stdio.h>

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

