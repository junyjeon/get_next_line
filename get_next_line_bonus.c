/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 20:28:00 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/29 22:08:13 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_node	*ft_lstnew(int fd, t_node **node)
{
	t_node	*element;

	element = (t_node *)malloc(sizeof(t_node));
	if (!element)
		return (0);
	element->read_size = read(node->fd, node->buf, BUFFER_SIZE);
	element->fd = fd;
	element->next = NULL;
	return (element);
}

int	check_fd(int fd, struct t_node **node);
{
	while (*node)
	{
		if (fd == (*node)->fd)
			return (1);
		*node = (*node)->next;
	}
	node->next = ft_lstnew(fd, &node);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_node	*buf = {NULL, 0, 0, BUFFER_SIZE};
	char	*tmp;

	if (fd < 0, read(buf->fd, buf->buf, BUFFER_SIZE) == -1) 
		return (0);
	while (1)
	{
		if (same_fd(fd, &buf))
			break ;
		// node->read_size = read(node->fd, node->buf, BUFFER_SIZE);
		if (node.read_size == -1)
			return (NULL);
		else if (node.read_size == 0)
			break ;
		node.buf[node.read_size] = '\0';
		tmp = lst;
		lst = lst.buf()에 buf_join하기
		lst_del()
		buf->read_size = read(buf->fd, buf->buf, BUFFER_SIZE);
		if (strchr(buf, '\n')
			break;
	}
	
}

