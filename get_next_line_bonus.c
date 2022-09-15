/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:01:32 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/16 07:21:31 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*buffer_join(int fd, char *buf, char *join)
{
	ssize_t		read_size;
	char		str[BUFFER_SIZE + 1];

	while (1)
	{
		read_size = read(fd, str, BUFFER_SIZE);
		if (read_size == 0)
			break ;
		str[read_size] = '\0';
		join = (char *)malloc(ft_strlen(buf) + read_size);
		if (!join)
			return (0);
		join = ft_strjoin(buf, str);
		if (ft_strchr(join, '\n'))
			break ;
	}
	return (join);
}

static char	*line_(char *join, char *line, t_node *node)
{
	int		join_len;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (join[i] && join[i] != '\n')
		i++;
	if (join[i] == '\n')
		i++;
	join_len = ft_strlen(join) - i;
	line = (char *)malloc(i);
	if (!line)
		return (0);
	j = -1;
	while (++j < i)
		line[j] = join[j];
	tmp = node->buf;
	node->buf = (char *)malloc(join_len);
	free(tmp);
	if (!node->buf)
		return (0);
	j = -1;
	while (++j < join_len)
		node->buf[j] = join[i + j];
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*join;
	char			*line;

	if (fd < 0 || read(fd, 0, 0) == -1)
		return (0);
	join = NULL;
	line = NULL;
	node = head;
	while (node || node->fd != fd)
		node = node->next;
	if (!node)
	{
		node->next = ft_lstnew(fd);
		node = node->next;
	}
	join = buffer_join(fd, node->buf, join);
	line = line_(0, 0, join, line, node);
	free(join);
	if (!line)
		clear_all(&head, fd);
	return (line);
}

#include <stdio.h>

int main()
{
	FILE *fd = fopen("test.txt", "r");

	printf("%s", get_next_line(fd));
	fclose(fd);
	return (0);
}
