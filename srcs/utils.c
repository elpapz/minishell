/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 05:16:35 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/23 02:00:26 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_varb	*create_var_list(char *name, char *value)
{
	t_varb	*new;

	new = malloc(sizeof(t_varb));
	new->var_name = name;
	new->var_value = value;
	new->next = NULL;
	return (new);
}