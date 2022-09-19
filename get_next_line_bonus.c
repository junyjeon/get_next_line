/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:01:32 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/19 21:53:26 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*buffer_join(int fd, char *buf, char *join)
{
	ssize_t		read_len;
	char		str[BUFFER_SIZE + 1];

	while (1)
	{
		read_len = read(fd, str, BUFFER_SIZE);
		if (read_len == 0)
			break ;
		str[read_len] = '\0';
		join = ft_strjoin(buf, str);
		if (ft_strchr(join, '\n'))
			break ;
	}
	return (join);
}

static char	*add_line(char *buf, char *line, char *join)
{
	size_t	i;
	size_t	join_len;
	char	*tmp;

	i = 0;
	if (!join)
		return (0);
	while (join[i] && join[i] != '\n')
		i++;
	if (join[i] == '\n')
		i++;
	join_len = ft_strlen(join) - i;
	line = ft_substr(join, 0, i);
	tmp = buf;
	buf = ft_substr(join, i, join_len);
	free(tmp);
	buf[join_len] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*node;
	char			*join;
	char			*line;

	if (fd < 0 && BUFFER_SIZE <= 0)
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
	line = add_line(node->buf, line, join);
	free(join);
	if (!line)
		clear_all(&head, fd, node->buf);
	return (line);
}

#include <fcntl.h>

int    main(void)
{
    int		fd;
    char	*line = NULL;

    fd = open("test2.txt", O_RDONLY);
    // while ((line = (get_next_line(fd))))
	for (int i = 0; i < 3; i++)
	{
		line = (get_next_line(fd));
    	printf("line : %s\n", line);
	}
    free(line);
}
// int main() {
// 	int	fd = open("test.txt", O_RDONLY);
//    	int i = 0;
// 	char* line;

// 	while (i < )
// 	{
// 		line = get_next_line(fd);
// 	printf("Gnl %d line : %s", i++, line);
//     /*while (line == get_next_line(fd))		// 2
//     {
//     	printf("Gnl %d line : %s", i++, line);	
//         free(line);				// 6	
//     }*/
//     printf("\n");

//     free(line);					// 4
// 	close(fd);				// 5
	
//     return (0);
// }
