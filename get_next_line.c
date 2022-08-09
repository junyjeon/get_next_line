/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:40 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/10 05:08:33 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_1(int fd, int read_size, char *buf, char **save)
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

char	*ft_2(int fd, char **save, char *line)
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
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save[fd] = ft_1(fd, read_size, buf, save);
	free(buf);
	line = ft_2(fd, save, line);
	return (line);
}

// #include <unistd.h>
// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	// int fd = open("./test2.txt", O_RDONLY);
// 	int fd;

// 	int i = 0;
// 	char *str;
// 	// while (i < 1)
// 	// {
// 	// 	str = get_next_line(fd);
// 	// 	printf("%d :[%s]", i + 1, str);
// 	// 	i++;
// 	// }
// 	fd = open("./test.txt", O_RDONLY);

// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", str);
// 	}	
// 	// system("LEAKS a.out");
// }

// "aa" + "ab" + "\nb"

// "12345n6n89" -> "123" "45n" + "6n8"
// "000000n000" -> "6789000000n" + "000"

// backup = "aaab\nb" -> line = "aaa\n"
// 				   -> backup = "b"
