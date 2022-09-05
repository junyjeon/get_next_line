/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_new.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:05:59 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/05 21:44:51 by junyojeo         ###   ########.fr       */
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
	while (str)
	{
		tmp = buf->buf;
		i = 0;
		while (i < ft_strlen(buf->buf) + BUFFER_SIZE)
			buf->buf[ft_strlen(buf->buf) + i] = str[i];
		buf->buf[ft_strlen(buf->buf) + i] = '\0';
		if (!buf->buf || buf->buf[0] == '\0')
		{
			free(buf->buf);
			buf->buf = 0;
			return (0);
		}
		free(tmp);
		i = -1;
		while (buf->buf[++i])
			if (buf->buf[i] == '\n')
				return (i);
		                                                                                                                                                                                                                                            
	}
	free(str);


}
