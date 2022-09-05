/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 20:28:00 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/05 18:05:28 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*output_line(int fd, t_node *buf, char *line)
{
	int		i;
	char	*tmp;
	
	if (!buf->buf || buf->buf[0] == '\0')
	{
		free(buf->buf);
		buf->buf = 0;
		return (NULL);
	}
	i = 0;
	while (buf->buf[i] != '\n' && buf->buf[i])
		i++;
	if (buf-buf[i] == '\n')
		i++;
	line = ft_substr(buf->buf, 0, i);
	if (!buf->buf[i])
	{
		free(buf->buf);
		buf->buf = 0;
		return (line);
	}
	tmp = buf;
	buf->next = ft_lstnew(fd, buf);
	buf = buf->next;
	lst_del(tmp);
	buf->buf = ft_substr(tmp, i, ft_strlen(buf->buf) - i);
	return (line);
}

t_node	*ft_lstnew(int fd, t_node *node)
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

int	same_fd(int fd, struct t_node *node);
{
	if (fd == node->fd)
		return (1);
	while (node)
		node = node->next;
	node->next = ft_lstnew(fd, node);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_node	*buf = {.next = NULL};
	t_node			*tmp;
	char			*line;

	if (fd < 0)
		return (0);
	while (1)
	{
		buf->read_size = read(buf->fd, buf->buf, BUFFER_SIZE);
		if (buf->read_size <= 0)
			return (0);
		buf->head = buf;
		buf->buf[buf->read_size] = '\0';
		if (same_fd(fd, buf->head))
		{
			buf->buf = (char *)malloc(1);
			buf->buf[0] = '\0';
		}
		tmp = buf;
		buf->buf = ft_strjoin(tmp->buf, buf->buf);
		free(tmp);
		lst_delete(tmp);
		buf->read_size = read(buf->fd, buf->buf, BUFFER_SIZE);
		if (ft_strchr(buf->buf, '\n')
			break;
	}
	free(buf->buf);
	line = output_line(fd, buf, line);
	
}

