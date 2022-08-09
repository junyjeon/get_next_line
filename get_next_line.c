/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:40 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/09 22:55:44 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// "12345n6n89" -> "123" "45n" + "6n8"
// "000000n000" -> "6789000000n" + "000"
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			read_size;
	size_t		i;
	static char	*backup[OPEN_MAX];
	char		*buf;
	char		*line;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_size = 1;
	while (read_size)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		else if (read_size == 0)
			break ;
		buf[read_size] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		tmp = backup[fd];
		backup[fd] = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = 0;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	buf = 0;
	if (!backup[fd] || backup[fd][0] == '\0')
	{
		free(backup[fd]);
		backup[fd] = 0;
		return (NULL);
	}
	i = 0;
	while (backup[fd][i] != '\n' && backup[fd][i])
		i++;
	if (backup[fd][i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line) 
		return (NULL);
	ft_memcpy(line, backup[fd], i);
	line[i] = '\0';
	if (!backup[fd][i]) ///case EOF
	{
		free(backup[fd]);
		backup[fd] = 0;
		return (line);
	}
	tmp = backup[fd];
	backup[fd] = ft_substr(tmp, i , ft_strlen(backup[fd]) - i);
	free(tmp);
	tmp = 0;
	return (line);
}

// #include <unistd.h>
// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
// 	int fd = open("./test.txt", O_RDONLY);

// 	int i = 0;
// 	char *str;
// 	while (i < 9)
// 	{
// 		str = get_next_line(fd);
// 		printf("%d :[%s]", i + 1, str);
// 		i++;
// 	}
// }
// "aa" + "ab" + "\nb"



// backup = "aaab\nb" -> line = "aaa\n"
// 				   -> backup = "b"
