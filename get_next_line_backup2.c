/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:40 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/09 21:28:24 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// "12345n6n89" -> "123" "45n" + "6n8"
// "000000n000" -> "6789000000n" + "000"
#include "get_next_line.h"

static char	*ft_(char *line)
{
	size_t		i;
	char		*tmp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (0);
	tmp = ft_strdup(&line[i + 1]);
	if (!tmp)
		return (NULL);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (tmp);
}

static char	*ft_read_line(int fd, char *buf, char *backup)
{
	int			read_size;
	char		*tmp;

	read_size = 1;
	while (read_size)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		else if (read_size == 0)
			break ;
		buf[read_size] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(tmp, buf);
		if (backup == NULL)
			return (NULL);
		free (tmp);
		tmp = 0;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || OPEN_MAX < fd || fd < 0)
		return (0);
	line = ft_read_line(fd, buf, backup[fd]);
	if (!line)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	backup[fd] = ft_(line);
	return (line);
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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
