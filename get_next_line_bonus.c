/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:22:15 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/24 09:59:39 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
static char	*buffer_join(int fd, char *backup)
{
	ssize_t	read_len;
	char	*tmp;
	char	*buf;

	read_len = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (read_len)
	{
		if (!backup)
		{
			backup = (char *)malloc(1);
			*backup = '\0';
		}
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1)
			return (0);
		buf[read_len] = '\0';
		printf("buf buffer_join: %s\n", buf);
		
		printf("before join backup buffer_join: %s\n", backup);
		tmp = backup;
		backup = ft_strjoin(tmp, buf);
		printf("backup malloced buffer_join: %p\n", backup);
		printf("after join backup buffer_join: %s\n", backup);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	printf("final backup buffer_join: %s\n", backup);
	free(buf);
	return (backup);
}

static char	*add_line(t_node *node)
{
	size_t	i;
	char	*line;
	char	*tmp;

	i = 0;
	while (node->backup[i] && node->backup[i] != '\n')
		i++;
	if (node->backup[i] == '\n')
		i++;
	tmp = node->backup;
	line = ft_substr(tmp, 0, i);
	node->backup = ft_substr(tmp, i, ft_strlen(tmp) - i);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	t_node			*prev;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!head)
	{
		head = (t_node *)malloc(sizeof(t_node));
		if (!head)
			return (0);
		head->next = NULL;
		head->backup = NULL;
		head->fd = 0;
	}
	node = head;
	while (node && fd != node->fd)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		node = ft_lstnew(fd, prev);
	printf("node get_next_line: %p\n", node);
	printf("node->backup get_next_line: %p\n", node->backup);
	node->backup = buffer_join(fd, node->backup);
	printf("node->backup get_next_line: %p\n", node->backup);
	line = add_line(node);
	if (!node->backup)
	{
		prev->next = node->next;
		free(node);
	}
	return (line);
}

// #include <fcntl.h>

// int    main(void)
// {
//     int		fd;
//     char	*line = NULL;

//     fd = open("test.txt", O_RDONLY);
// 	for (int i = 0; i < 3; i++)
// 	{
// 		line = (get_next_line(fd));
//     	printf("line : %s", line);
// 	}
// 	free(line);
// }
