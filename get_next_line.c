/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:43:40 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/08 20:05:41 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// "12345n6n89" -> "123" "45n" + "6n8"
// "000000n000" -> "6789000000n" + "000"
#include <stdio.h>
#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	size_t		i;
	int			size;
	static char	*backup[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;

	if (BUFFER_SIZE <= 0 || OPEN_MAX < fd || fd < 0)
		return (0);
	while (!backup[fd] || !(ft_strchr(backup[fd], '\n')))
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		else if (size == 0)
			break ;
		buf[size] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		tmp = backup[fd];
		backup[fd] = ft_strjoin(tmp, buf);
		free (tmp);
		tmp = 0; 
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (!backup[fd] || backup[fd][0] == '\0')
	{
		if (backup[fd] && backup[fd][0] == '\0')
		{
			free(backup[fd]);
			backup[fd] = 0;
		}
		return (NULL);
	}
	// printf("backup:1 (%s)\n", backup[fd]);
	i = 0;
	while (backup[fd][i] != '\n' && backup[fd][i])
		i++;
	line = malloc(sizeof(char) * i + 2);
	ft_memcpy(line, backup[fd], i + 1);
	line[i + 1] = '\0';
	if (!backup[fd][i])
	{
		free(backup[fd]);
		backup[fd] = 0;
		return (line);
	}
	tmp = backup[fd];
	backup[fd] = ft_substr(backup[fd], i + 1, ft_strlen(backup[fd]) - i);
	// printf("[back : %s]\n", backup[fd]);
	free(tmp);
	tmp = 0;
	// printf("line: (%s)\n", line);
	return (line);
}

// #include <unistd.h>
// #include <fcntl.h>

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
