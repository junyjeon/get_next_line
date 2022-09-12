/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus_333.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:01:32 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/12 21:30:54 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

typedef struct s_node
{
	struct t_node	*head;
	struct t_node	*next;
	ssize_t			cnt;
	size_t			cur_cnt;
	size_t			ent_idx;
	char			*buf;
}	t_node;

t_node	*ft_lstnew(int fd, t_node *node)
{
	t_node	*element;

	element = (t_node *)malloc(sizeof(t_node));
	if (!element)
		return (0);
	element->head = node->head;
	element->next = NULL;
	element->buf = (char *)malloc(BUFFER_SIZE + 1);
	if (element->buf)
		return (0);
	element->cnt = read(fd, element->buf, BUFFER_SIZE);
	if (element->cnt <= 0)
		return (0);
	while (node)
		node = node->next;
	node->next = element;
	return (node);
}

char	*get_next_line(int fd)
{
	static t_node	*node;
	int				i;
	char			*line;

	if (fd < 0 || read(fd, 0, 0) <= 0)
		return (0);
	node->head = node;
	node->next = NULL;
	while (1)
	{
		ft_lstnew(fd, node);
		node->buf[ft_strlen(node->buf)] = '\0';


	}
	return (line);
}
