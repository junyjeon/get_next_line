/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_new.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:05:59 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/05 20:30:28 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line_bonus.h"

typedef struct s_node
{
	struct t_node	*head;
	struct t_node	*next;
	ssize_t			read_size;
	int				fd;
	char			buf[BUFFER_SIZE];
}	t_node;

char	*get_next_line(int fd)
{
	static t_node	*buf = {.head = buf .fd = fd, .next = NULL};
	t_node			*tmp_node;
	int				i;
	char			*tmp;
	char			*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(buf->buf) + BUFFER_SIZE));
	if (fd < 0, read(fd, str, BUFFER_SIZE) == -1, !str)
		return (0);
	while (1)
	{
		tmp = buf->buf;
		i = 0;
		while (i < ft_strlen(buf->buf) + BUFFER_SIZE)
			buf->buf[ft_strlen(buf->buf) + i] = str[i];
		free(tmp);

	}
}
