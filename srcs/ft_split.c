/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 07:56:09 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/15 03:10:17 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	word_index(const char *s)
{
	int	index = 0;
	int	words = 0;

	while (*s)
	{
		if (*s != ' ' && *s != '\t' && index == 0)
		{
			index = 1;
			words++;
		}
		else if (*s == ' ' || *s == '\t')
			index = 0;
		s++;
	}
	return (words);
}

int	letter_index(const char *s, int i)
{
	int	j = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i])
	{
		i++;
		j++;
	}
	return (j);
}

char	**ft_split(const char *s)
{
	int	i = 0;
	int	j = 0;
	//int	a = 0;
	int	words = word_index(s);
	char	**splited;
	//printf("%d\n", words);

	splited = malloc(sizeof(char *) * words + 1);
	if (!splited)
		return (NULL);
	while (j < words)
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		splited[j] = malloc(sizeof(char) * letter_index(s, i) + 1);
		if (!splited[j])
			return (NULL);
		int a = 0;
		while (s[i] != ' ' && s[i] != '\t' && s[i])
		{
			splited[j][a] = s[i];
			a++;
			i++;
		}
		splited[j][a] = 0;
	j++;
	}
	splited[j] = 0;
	return (splited);
}

int		main(void)
{
	char	*str = "     caralho     'ola' ";
	char **splited;
	int		a;
	a = 0;
	splited = ft_split(str);
	while (splited[a])
	{
		printf ("%s\n", splited[a]);
		a++;
	}
}