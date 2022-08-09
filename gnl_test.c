/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:54:21 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/09 22:27:19 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



char	*get_next_line(int fd)
{
	size_t		i;
	int			read_size;
	static char *backup[OPEN_MAX];
	char		*new_line;
	char		*buf;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || OPEN_MAX < fd)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_size = 1;
	while (read_size)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		else if (!read_size)
			break ;
		buf[read_size] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		tmp = backup[fd];
		backup[fd] = ft_strjoin(tmp, buf);
		if (!backup[fd])
			return (NULL);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(backup[fd], '\n'))
		{
			while (backup[fd][i] != '\n' || backup[fd][i] != '\n')
				i++;
			if (backup[fd][i] == '\n')
				i++;
			tmp = backup[fd];
			backup[fd] = ft_substr(backup[fd], i, read_size - i);
			if (!backup[fd])
				return (NULL);
			tmp[i] = '\0';
			line = ft_strdup(tmp);
			free(tmp);
			tmp = 0;
		}
		else
			line = ft_strdup(backup[fd]);
	}
	return (line);
}

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd = open("./test.txt", O_RDONLY);
	int i = 0;
	char *str;
	while (i < 12)
	{
		str = get_next_line(fd);
		printf("%d :[%s]", i + 1, str);
		i++;
	}
}
