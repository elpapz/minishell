/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 05:49:18 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/11 06:11:53 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void organize_strings(char **new_envp)
{
    char *temp;
    int i, j;

    i = 0;
    while (new_envp[i] != NULL)
	{
        j = i + 1; // Começa a verificação na próxima posição
        while (new_envp[j] != NULL)
		{
            if (ft_strncmp(new_envp[i], new_envp[j], ft_strlen(new_envp[j])) > 0)
			{
                temp = new_envp[i];
                new_envp[i] = new_envp[j];
                new_envp[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void exec_export(char *input, char **envp)
{
	//(void)input;
    char **new_envp;
    int i = 0;
	int check;

	check = 0;
    while (envp[i] != NULL)
	{
        i++;
    }

    new_envp = malloc((i + 1) * sizeof(char *));

    if (new_envp == NULL)
	{
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    //copiar
    for (int j = 0; j < i; j++)
	{
        new_envp[j] = malloc(strlen(envp[j]) + 1);
        if (new_envp[j] == NULL) {
            perror("Erro ao alocar memória");
            exit(EXIT_FAILURE);
        }
        strcpy(new_envp[j], envp[j]);
    }

    new_envp[i] = NULL;
	if(strncmp(input,"export",6) == 0)
		check = 1;
	if(check == 1)
		organize_strings(new_envp);

	//imprimir para checkar
	//depois para imprimir certo o export posso imprimir ate o '='
	//depois imprimir '"'
	//acaba de imprimir ate o '\n' com o '\n' fora do output
	//imprimi '"' e um \n e ta feito
    i = 0;
    while (new_envp[i] != NULL)
	{
		//if(check == 1)
		//	ft_printf("declare -x ");
        printf("%s\n", new_envp[i]);
        i++;
    }

    // free memory
    for (int j = 0; j < i; j++)
	{
        free(new_envp[j]);
    }
    free(new_envp);
}