/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_new.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:05:59 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/05 23:12:29 by junyojeo         ###   ########.fr       */
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

	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str, fd < 0, read(fd, str, BUFFER_SIZE) == -1)
		return (0);
	while (str)
	{
		tmp = buf->buf;
		buf->buf = (char *)malloc(ft_strlen(buf->buf) + ft_strlen(str));
		if (!buf->buf)
			return (0);
		i = 0;
		while (str)
			buf->buf[ft_strlen(buf->buf) + i] = str[i++];
		buf->buf[ft_strlen(buf->buf) + i] = '\0';
		if (!buf->buf || buf->buf[0] == '\0')
		{
			free(buf->buf);
			buf->buf = 0;
			return (0);
		}
		free(tmp);
		i = -1;
		while (buf->buf)
			if (buf->buf[++i] == '\n')
				return (i);
		read(fd, str, BUFFER_SIZE);
	}
	while (buf->buf[i] != '\n' && buf->buf[i])
		i++;
	if (buf->buf[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (0);
	line[i] = '\0';
	while (--i)
		line[i] = buf->buf[i];
	tmp = buf->buf;
	buf->buf = (char *)malloc(ft_strlen(tmp) - i);
	if (!buf->buf)
		return (0);
	buf->buf[ft_strlen(buf->buf)] = '\0';
	i = 0;
	while (buf->buf)
		buf->buf[i] = tmp[i];
	free(tmp);
	free(str);
	return (line);
}
