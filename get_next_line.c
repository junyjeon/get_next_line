/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:40 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/22 05:33:05 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buf_read(int fd, char *buf, char *save)
{
	ssize_t		read_size;
	char		*tmp;

	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		buf[read_size] = '\0';
		if (read_size <= 0)
			break ;
		if (!save)
		{
			save = ft_strdup("");
			save[0] = '\0';
		}
		tmp = save;
		save = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (save);
}

char	*split_idx(int fd, char **save, char *line)
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
	static char	*save[OPEN_MAX];
	char		*buf;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save[fd] = buf_read(fd, buf, save[fd]);
	free(buf);
	line = split_idx(fd, save, line);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int    main(void)
// {
//     int		fd;
//     char	*line = NULL;

//     fd = open("test2.txt", O_RDONLY);
// 	line = (get_next_line(fd));
//    	printf("line : %s\n", line);
// }
