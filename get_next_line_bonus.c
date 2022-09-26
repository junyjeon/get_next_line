/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:22:15 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/26 20:28:05 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*buffer_join(int fd, t_node *lst)
{
	ssize_t	read_len;
	char	*tmp;
	char	*buf;

	read_len = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (read_len)
	{
		if (!lst->backup)
		{
			lst->backup = (char *)malloc(1);
			lst->backup[0] = '\0';
		}
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1)
			return (0);
		buf[read_len] = '\0';
		tmp = lst->backup;
		lst->backup = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (lst->backup);
}

static char	*add_line(t_node *lst, char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	tmp = lst->backup;
	line = ft_substr(tmp, 0, i);
	lst->backup = ft_substr(tmp, i, ft_strlen(tmp) - i);
	if (tmp)
		free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*lst;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	lst = head;
	while (lst && fd != lst->fd)
		lst = lst->next;
	if (!lst)
		lst = ft_lstnew(fd, &head);
	line = buffer_join(fd, lst);
	line = add_line(lst, line);
	if (!line)
		free_lst(head, fd);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int    main(void)
{
    int		fd;
    char	*line = NULL;

    fd = open("test.txt", O_RDONLY);
	for (int i = 0; i < 3; i++)
	{
		line = (get_next_line(fd));
		system("leaks a.out");
    	printf("line : %s", line);
	}
	free(line);
}
