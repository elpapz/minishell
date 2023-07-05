/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warm_up_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 04:21:38 by acanelas          #+#    #+#             */
/*   Updated: 2023/07/05 03:17:10 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE
#define _POSIX_C_SOURCE >= 199309L
#define _GNU_SOURCE

#include "../minishell.h"
extern long long g_exit_status;
//got to init the INFO STRUCT and the ENVP
void	cntrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	define_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = &cntrl_c;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);

}

char	**divide_envp(char *str)
{
	char	**env_var;
	int	i;

	i = 0;
	env_var = malloc(sizeof(char *) * 2);
	while (str[i] != '=')
		i++;
	env_var[0] = ft_substr(str, 0, i);
	env_var[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (env_var);
	
}

void	fill_envp_list(char **envp, t_info *info)
{
	t_varb	*head;
	t_varb	*temp;
	char	**var_line;
	int	i;

	var_line = divide_envp(envp[0]);
	head = create_var_list(var_line[0], var_line[1]);
	i = 0;
	temp = head;
	while (envp[++i])
	{
		free(var_line);
		var_line = divide_envp(envp[i]);
		temp->next = create_var_list(var_line[0], var_line[1]);
		temp = temp->next;
	}
	free (var_line);
	return (head);
}


void	warm_up_shell(char **envp, t_info *info)
{
	info->envp = envp;
	fill_envp_list(envp, info);
	rl_clear_history();
}