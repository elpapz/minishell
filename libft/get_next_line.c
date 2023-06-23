/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 01:22:07 by acanelas          #+#    #+#             */
/*   Updated: 2022/11/23 01:23:04 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_search(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

static	char	*next_line(char *main_buff)
{
	int		x;
	int		y;
	char	*next;

	x = 0;
	y = 0;
	while (main_buff[x] && main_buff[x] != '\n')
		x++;
	if (!main_buff[x])
	{
		free(main_buff);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(main_buff) - x + 1), sizeof(char));
	if (!next)
		return (NULL);
	x++;
	while (main_buff[x])
		next[y++] = main_buff[x++];
	next[y] = '\0';
	free (main_buff);
	return (next);
}

static	char	*read_all(char *main_buff, int fd)
{
	char	*buff;
	int		bytes;

	bytes = 1;
	if (main_buff == NULL)
			main_buff = ft_calloc(1, sizeof(char));
		buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == (-1))
		{
			free(main_buff);
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		main_buff = ft_strjoin(main_buff, buff);
		if (char_search(main_buff, '\n') > 0)
			break ;
	}
	free(buff);
	return (main_buff);
}

static	char	*final_line(char *main_buff)
{
	int		len;
	int		i;
	char	*final;

	len = 0;
	i = 0;
	if (!main_buff[i])
		return (NULL);
	while (main_buff[len] && main_buff[len] != '\n')
		len++;
	final = ft_calloc(len + 2, sizeof(char));
	if (!final)
		return (NULL);
	while (i <= len)
	{
		final[i] = main_buff[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}

char	*get_next_line(int fd)
{
	static char		*main_buff;
	char			*line_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	main_buff = read_all(main_buff, fd);
	if (!main_buff)
		return (NULL);
	line_read = final_line(main_buff);
	main_buff = next_line(main_buff);
	return (line_read);
}


int		main(void)
{
	int	fd;
	char	*line;

	fd = open("get_next_line.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%d\n%s\n", fd, line);

	line = get_next_line(fd);
	printf("%d\n%s\n", fd, line);
	//close(fd);

	fd = open("gnlTester/files/get_next_line.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%d\n%s\n", fd, line);
	
	line = get_next_line(fd);
	printf("%d\n%s\n", fd, line);

	line = get_next_line(fd);
	printf("%d\n%s\n", fd, line);
	

	
}

