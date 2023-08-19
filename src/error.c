#include "../include/minishell.h"

bool error(char *str,char str_extra)
{
	write(2,str,ft_strlen(str));
	if(str_extra)
	{
		write(2, " ", 1);
		ft_putchar_fd(str_extra, STDERR_FILENO);
		write(2,"\n",1);
	}
	return (false);
}
