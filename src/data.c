#include "../include/minishell.h"

/*
t_varlst *get_var(char **envp)
{
	t_varlst *new_var;
	t_varlst *head_var;
	t_varlst *temp_var;
	int num_strings;
	char **var;

	num_strings = 0;
	head_var = NULL;
	temp_var = NULL;
	while(envp[num_strings])
	{
		new_var = malloc(sizeof(t_varlst));
		if(!new_var)
			error(MALLOC,NULL);
		var = ft_split(envp[num_strings],'=');
		new_var->var_name = malloc(sizeof(char) * (ft_strlen(var[0]) + 1));
		ft_strcpy(new_var->var_name,var[0]);
		if(!var[1])
		{
			new_var->var_value = malloc(1);
			new_var->var_value[0] = 0;
		}
		else
		{
			new_var->var_value = malloc(sizeof(char) * (ft_strlen(var[1]) + 1));
			ft_strcpy(new_var->var_value,var[1]);
		}
		new_var->next = NULL;
		if(!head_var)
		{
			head_var = new_var;
			temp_var = head_var;
		}
		else
		{
			temp_var->next = new_var;
			temp_var = temp_var->next;
		}
		num_strings++;
	}
	return head_var;
}
*/

t_statlst *get_stat(int ac, char **av)
{
	t_statlst *temp_stat;

	temp_stat = malloc(sizeof(t_statlst));
	if(!temp_stat)
	{
		ft_putstr_fd(MALLOC, STDERR_FILENO);
		return (NULL);
	}
	temp_stat->ac = ac;
	temp_stat->av = av;
	temp_stat->next = NULL;
	return (temp_stat);
}

t_varlst	*create_var_list(char *name, char *value)
{
	t_varlst	*new;

	new = malloc(sizeof(t_varlst));
	if(!new)
	{
		ft_putstr_fd(MALLOC, STDERR_FILENO);
		return (NULL);
	}
	new->var_name = name;
	new->var_value = value;
	new->next = NULL;
	return (new);
}

char	**divide_envp(char *str)
{
	char	**env_var;
	int	i;

	i = 0;
	env_var = malloc(sizeof(char *) * 2);
	if (!env_var)
	{
		ft_putstr_fd(MALLOC, STDERR_FILENO);
		return (NULL);
	}
	while (str[i] != '=')
		i++;
	env_var[0] = ft_substr(str, 0, i);
	env_var[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (env_var);
	
}

t_varlst	*fill_envp_list(char **envp)
{
	t_varlst	*head;
	t_varlst	*temp;
	char	**var_lines;
	int	i;

	var_lines = divide_envp(envp[0]);
	head = create_var_list(var_lines[0], var_lines[1]);
	i = 0;
	temp = head;
	while (envp[++i])
	{
		free(var_lines);
		var_lines = divide_envp(envp[i]);
		temp->next = create_var_list(var_lines[0], var_lines[1]);
		temp = temp->next;
	}
	free (var_lines);
	return (head);
}

t_data *get_data(int ac, char **av, char **envp)
{
	t_data *temp_data;

	temp_data = (t_data *)malloc(sizeof(t_data));
	if(!temp_data)
	{
		ft_putstr_fd(MALLOC, STDERR_FILENO);
		return (NULL);
	}
	temp_data->envp = envp;
	temp_data->stat_head = get_stat(ac, av);
	temp_data->var_head = fill_envp_list(envp);
	temp_data->check_out = false;
	temp_data->check_in = false;
	return (temp_data);
}
