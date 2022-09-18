/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:01:32 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/18 19:32:23 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"

static char	*buffer_join(int fd, char *buf, char *join)
{
	ssize_t		read_len;
	char		str[BUFFER_SIZE + 1];
//
	while (1)
	{
		read_len = read(fd, str, BUFFER_SIZE);
		if (read_len == 0)
			break ;
		str[read_len] = '\0';
		printf("%s\n",buf);
		join = ft_strjoin(buf, str);
		if (ft_strchr(join, '\n'))
			break ;
	}
	return (join);
}

static char	*add_line(t_node *node, char *line, char *join)
{
	size_t	i;
	size_t	j;
	size_t	join_len;
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
	node->buf = (char *)malloc(join_len + 1);
	free(tmp);
	if (!node->buf)
		return (0);
	j = i - 1;
	while (++j < join_len)
		node->buf[j] = join[i + j];
	node->buf[join_len] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*join;
	char			*line;

	printf("%d",fd);
	if (fd < 0 || read(fd, 0, 0) == -1)
		return (0);
	if (!head)
		head = ft_lstnew(fd);
	node = head;
	join = NULL;
	line = NULL;
	while (node && fd != node->fd)
		node = node->next;
	if (!node)
		node = ft_lstnew(fd);
	join = buffer_join(fd, node->buf, join);
	line = add_line(node, line, join);
	free(join);
	if (!line)
		clear_all(&head, fd);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int main() {
	char* line;
	int	fd;
   	int i = 1;

	printf("00");
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("Gnl %d line : %s", i++, line);
    /*while (line == get_next_line(fd))		// 2
    {
    	printf("Gnl %d line : %s", i++, line);	
        free(line);				// 6	
    }*/
    printf("\n");

    free(line);					// 4
	close(fd);				// 5
	
    return (0);
}
