/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:40 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/10 06:01:42 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*buf_read(int fd, int read_size, char *buf, char **save)
{
	char		*tmp;

	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		else if (read_size == 0)
			break ;
		buf[read_size] = '\0';
		if (!save[fd])
		{
			save[fd] = ft_strdup("");
			save[fd][0] = '\0';
		}
		tmp = save[fd];
		save[fd] = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (save[fd]);
}

char	*set_line_and_save(int fd, char **save, char *line)
{
	int			i;
	char		*tmp;

	if (!save[fd] || save[fd][0] == '\0')
	{
		free(save[fd]);
		save[fd] = 0;
		return (NULL);
	}
	i = 0;
	while (save[fd][i] != '\n' && save[fd][i])
		i++;
	if (save[fd][i] == '\n')
		i++;
	line = ft_substr(save[fd], 0, i);
	if (!save[fd][i])
	{
		free(save[fd]);
		save[fd] = 0;
		return (line);
	}
	tmp = save[fd];
	save[fd] = ft_substr(tmp, i, ft_strlen(save[fd]) - i);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	int			read_size;
	static char	*save[OPEN_MAX];
	char		*buf;
	char		*line;

	line = NULL;
	read_size = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	exit(1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save[fd] = buf_read(fd, read_size, buf, save);
	free(buf);
	line = set_line_and_save(fd, save, line);
	return (line);
}

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	// int fd = open("./test2.txt", O_RDONLY);
	int fd;

	char *str;
	// while (i < 1)
	// {
	// 	str = get_next_line(fd);
	// 	printf("%d :[%s]", i + 1, str);
	// 	i++;
	// }
	fd = open("./test.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("[%s]", str);
	}	
	system("LEAKS a.out");
}
