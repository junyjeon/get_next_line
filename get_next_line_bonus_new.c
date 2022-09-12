/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_new.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:05:59 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/12 20:57:23 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

typedef struct s_node
{
	struct t_node	*head;
	struct t_node	*next;
	ssize_t			read_size;
	int				fd;
	char			buf[BUFFER_SIZE];
}	t_node;

t_node	*ft_lstnew(int fd, t_node *node)
{
	t_node	*element;

	element = (t_node *)malloc(sizeof(t_node));
	if (!element)
		return (0);
	element->fd = fd;
	element->head = node->head;
	element->next = NULL;
	element->read_size = read(fd, element->buf, BUFFER_SIZE);
	if (element->read_size <= 0)
		return (0);
	while (node)
		node = node->next;
	node->next = element;
	return (node);
}

char	*get_next_line(int fd)
{
	static t_node	*node;
	t_node			*tmp_node;
	int				i;
	char			*str;
	char			*tmp;

	if (fd < 0 || read(fd, 0, 0) == -1)
		return (0);
	while (1)
	{
		if (node->fd == fd)
			node->next = ft_lstnew(fd, node);
		if (node->read_size == 0)
		{
			node->buf = malloc(1);
			node->buf[0] = '\0';
		}
		node->buf[node->read_size] = '\0';
		str = (char *)malloc(ft_strlen(node->buf) + node->read_size);
		if (!str)
			return (0);
		i = -1;
		while (str[++i] || str[i] != '\n')
			node->buf[i] = str[i];
		node->buf[ft_strlen(node->buf) + i] = '\0';
		if (!node->buf || node->buf[0] == '\0')
		{
			free(node->buf);
			node->buf = 0;
			return (0);
		}
		free(tmp);
		i = -1;
		while (node->buf[i])
			if (node->buf[++i] == '\n')
				return (i);
		if (!read(fd, str, BUFFER_SIZE))
			return (0);
	}
	line = (char *)malloc(i + 1);
	if (!line)
		return (0);
	line[i] = '\0';
	j = 0;
	while (j < i)
		line[j] = node->buf[j++];
	tmp = str;
	str = (char *)malloc(ft_strlen(node->buf) - i);
	if (!str)
		return (0);
	str[ft_strlen(line)] = '\0';
	while (node->buf[i])
		node->buf[i] = tmp[i + j];
	free(tmp);
	lst_clear();
	return (line);
}

#include <stdio.h>
int main()
{
	int		i;
	FILE	*fd = fopen("test.txt", "r");
	char	*str;

	while (1)
	{
		str = get_next_line(fd);
		printf("%s\n", str);
		if (feof(fd))
			break ;
	}
	fclose(fd);
}
