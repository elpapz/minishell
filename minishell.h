/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 00:33:59 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/23 02:01:22 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHEL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_args
{
	char			**av;
	int				ac;
	struct s_args	*next;
}					t_args;

typedef struct s_varb
{
	char		*var_name;
	char		*var_value;
	bool		is_exported;
	struct s_var	*next;
}				t_varb;

typedef struct s_info
{
	char	**envp;
	t_varb	*evnp_lst;
	t_args	*head;

}			t_info;

t_varb	*create_var_list(char *name, char *value);


#endif