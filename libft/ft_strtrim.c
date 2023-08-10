/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:45:48 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/10 06:29:05 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

/*
static int		find_char(const char *str, char c)
{
	int		a;

	a = 0;
	while (str[a])
	{
		if (str[a] == c)
		{
			return (1);
		}
			a++;
	}
	return(0);
}
*/
/*
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	inicio;
	size_t	final;
	size_t	result;
	size_t	rvresult;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	inicio = 0;
	final = ft_strlen(s1);
	rvresult = final -1;
	while ((find_char(set, s1[inicio]) > 0) && s1[inicio])
		inicio++;
	while ((find_char(set, s1[rvresult]) > 0) && (final) > inicio)
	{
		rvresult--;
		final--;
	}

	trimmed = (char *)malloc(sizeof(char) * (final - inicio + 1));
	if (!trimmed)
		return (NULL);
	result = 0;
	while (final > inicio && s1[inicio])
	{
		trimmed[result] = s1[inicio];
		result++;
		inicio++;
	}
	trimmed[result] = '\0';
	return (trimmed);
}
*/
/*
int		main(void)
{
	char *s1 = "aaaabbaaadddddbcccccccddddddd";
	char *s2 = "ad";
	printf("%s", ft_strtrim(s1, s2));
}
*/
static int	find_char(const char *str, char c)
{
	int		a;

	a = 0;
	while (str[a])
	{
		if (str[a] == c)
		{
			return (1);
		}
			a++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	inicio;
	size_t	final;
	size_t	rvresult;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	inicio = 0;
	final = ft_strlen(s1);
	rvresult = final -1;
	while ((find_char(set, s1[inicio]) > 0) && s1[inicio])
		inicio++;
	while ((find_char(set, s1[rvresult]) > 0) && (final) > inicio)
	{
		rvresult--;
		final--;
	}
	trimmed = ft_substr(s1, inicio, final - inicio);
	return (trimmed);
}

/*
int		main(void)
{
	char *s1 = " 		  cd Desktop 	";
	char *s2 = " \t";
	printf("%s", ft_strtrim(s1, s2));
}
*/
