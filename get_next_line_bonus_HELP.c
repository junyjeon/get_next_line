/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_HELP.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 05:26:58 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/27 05:31:37 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

typedef struct s_lst
{
	struct s_lst	*next;
	char			*backup;
	int				fd;
}	t_lst;

char	*get_next_line(int fd)
{
	static t_lst	*head;
	t_lst			*lst;
	ssize_t			read_size;
	size_t			i;
	size_t			j;
	char			*buf;
	char			*str;
	char			*line;
	char			*tmp;

	lst = head;
	while (lst && lst->fd != fd)
		lst = lst->next;
	if (!lst)
	{
		lst = (t_lst *)malloc(sizeof(t_lst));
		if (!lst)
			return (0);
		lst->backup = 0;
		lst->fd = fd;
		if (!head)
		{
			lst->backup = (char *)malloc(sizeof(char) + 1);
			if (!lst->backup)
				return (0);
			lst->backup[0] = '\0';
			head = lst;
			lst->next = 0;
		}
		else
		{
			lst->next = head;
			head = lst;
		}
		lst->next = head;
		head = lst;
	}
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (0);
		if (!read_size)
			break ;
		buf[read_size] = '\0';
		tmp = lst->backup;
		str = (char *)malloc(ft_strlen(lst->backup) + read_size + 1);
		if (!str)
			return (0);
		if (lst->backup)
		{
			i = -1;
			while (lst->backup[++i])
				str[i] = lst->backup[i];
		}
		j = -1;
		while (buf[++j])
			str[i + j] = buf[j];
		str[i + j] = '\0';
		free(tmp);
		tmp = 0;
		i = -1;
		while (buf[++i])
			if (buf[i] == '\n')
				break ;
	}
	free(buf);
	line = 0;
	if (str)
	{
		i = 0;
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
		line = (char *)malloc(sizeof(char) * (i + 1));
		j = -1;
		while (++j < i)
			line[j] = str[j];
		tmp = lst->backup;
		lst->backup = (char *)malloc(ft_strlen(lst->backup) - i + 1);
		while (str[++i])
			*(lst->backup++) = str[i];
		*lst->backup = '\0';
		free(tmp);
		tmp = 0;
	}
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
	getchar();
}

