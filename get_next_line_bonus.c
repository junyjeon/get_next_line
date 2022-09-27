/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:22:15 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/27 09:08:03 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	free_lst(t_node *head, int fd)
{
    t_node	*prev;
    t_node	*seek;

	seek = head;
    if (head->fd == fd)
    {
		head = seek->next;
		free(head->backup);
		free(seek);
        return ;
    }
    while (seek)
    {
        if (seek->fd == fd)
        {
            prev->next = seek->next;
			free(seek->backup);
            free(seek);
            return;
        }
        prev = seek;
        seek = seek->next;
    }
}

static char	*buffer_join(int fd, t_node *lst)
{
	ssize_t	read_len;
	char	*tmp;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_len = read(fd, buf, BUFFER_SIZE);
	while (read_len && read_len != -1)
	{
		if (read_len == -1)
			return (0);
		buf[read_len] = '\0';
		if (!lst->backup)
		{
			lst->backup = (char *)malloc(1);
			if (lst->backup == NULL)
			{
				free(buf);
				return (NULL);
			}
			lst->backup[0] = '\0';
		}
		tmp = lst->backup;
		lst->backup = ft_strjoin(lst->backup, buf);
		free(tmp);
		tmp = 0;
		// if (lst->backup == NULL)
		// 	return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
		read_len = read(fd, buf, BUFFER_SIZE);
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
	if (!tmp)
		return (0);
	line = ft_substr(lst->backup, 0, i);
	lst->backup = ft_substr(lst->backup, i, ft_strlen(lst->backup) - i);
	if (tmp)
		free(tmp);
	tmp = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*lst;
	char			*tmp;
	char			*line;

	lst = head;
	while (lst && fd != lst->fd)
		lst = lst->next;
	if (!lst)
		lst = ft_lstnew(fd, &head);
	tmp = buffer_join(fd, lst);
	line = NULL;
	if (tmp)
		line = add_line(lst, tmp);
	if (!line && lst->backup)
		free_lst(head, fd);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>
int    main(void)
{
    int		fd[3];
    char	*line = NULL;

    fd[0] = open("test.txt", O_RDONLY);
    fd[1] = open("test copy.txt", O_RDONLY);
    fd[2] = open("test copy 2.txt", O_RDONLY);
	for (int i = 0; i < 3; i++)
	{
		line = (get_next_line(fd[i]));
    	printf("line : %s", line);
		free(line);
	}
	for (int i = 0; i < 3; i++)
	{
		line = (get_next_line(fd[i]));
    	printf("line : %s", line);
		free(line);
	}
	for (int i = 0; i < 3; i++)
	{
		line = (get_next_line(fd[i]));
    	printf("line : %s", line);
		free(line);
	}
	//system("leaks a.out");
	// getchar();
}
