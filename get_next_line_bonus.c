/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:22:15 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/21 18:23:16 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*buffer_join(int fd, char *buf, char *str)
{
	ssize_t		read_len;
	char		*tmp;

	while (1)
	{
		read_len = read(fd, str, BUFFER_SIZE);
		if (read_len == -1)
			return (0);
		str[read_len] = '\0';
		if (read_len == 0)
			break ;
		tmp = buf;
		buf = ft_strjoin(tmp, str);
		free(tmp);
		if (!buf)
			return (0);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (buf);
}

static char	*add_line(char *buf, char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = ft_substr(buf, 0, i);
	if (!line)
		return (0);
	tmp = buf;
	buf = ft_substr(buf, i, ft_strlen(buf) - i);
	free(tmp);
	if (!buf)
		return (0);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*line;
	char			str[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!head)
	{
		head = ft_lstnew(fd);
		if (!head)
			return (0);
	}
	node = head;
	if (head->next)
	{
		while (node && fd != node->fd)
			node = node->next;
		if (!node)
		{
			node = ft_lstnew(fd);
			if (!node)
				return (0);
		}
	}
	node->buf = buffer_join(fd, node->buf, str);
	line = 0;
	if (node->buf)
	{
		line = add_line(node->buf, line);
		if (!line)
			return (0);
	}
	clear_all(head, fd, node->buf);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int    main(void)
// {
//     int		fd;
//     char	*line = NULL;

//     fd = open("test2.txt", O_RDONLY);
// 	for (int i = 0; i < 3; i++)
// 	{
// 		line = (get_next_line(fd));
//     	printf("line : %s\n", line);
// 	}
// }
