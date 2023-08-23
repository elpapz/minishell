#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

char *get_input(void)
{
	char *input;
	char *temp;

	temp = readline("\033[0;32mminishell $>\033[0m ");
	input = ft_strtrim(temp," \t");
	free(temp);
	return (input);
}

void	cntr_d(char *input, t_data **data)
{
	if (!input)
	{
		rl_clear_history();
		ft_putendl_fd("exit", STDOUT_FILENO);
		free_data(data);
		exit(EXIT_SUCCESS);
	}
}

void	print_tokens(t_tokens *head)
{
	t_tokens	*tmp = head;
	while (tmp->next != NULL)
	{
		printf("%s\n", tmp->command);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	int temp_stdout;
	int temp_stdin;

	if(ac > 1 && av)
		exit (error(ARGS,'\0'));
	data = get_data(ac,av,envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while(1)
	{
		//reset();
		dup2(temp_stdout,STDOUT_FILENO);
		dup2(temp_stdin,STDIN_FILENO);
		input = get_input();
		cntr_d(input, &data);
		if(!input[0] || !check_input(input))
		{
			free_data(&data);
			free(input);
		}
		else
		{
			add_history(input);
			/*tokens divididos por: ' ' por: '\t e pela existencia de quotes: done
			munanças estao no tokens.c, o tester é a funcao print_tokens*/
			data->tokens_head = get_tokens(data, input);
			print_tokens(data->tokens_head);
			//data->check_in = false;
			if(!strncmp(data->tokens_head->command,"exit",4))
			{/*preciso retirar as quotes aos tokens e checkar se os tokens em sim sâo validos
			ou nao, expansiveis ou nao e tratar disso*/
				free_data(&data);
				free_tokens(data); // dá segfault quando escrevo exit, se tirar esta funcao daqui ja não dá segfault!
				break;
			}
			exec_tokens(data);
			unlink(TEMP_FILE);
			free_tokens(data);
			
		}
	}
	return 0;
}
