/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:20:08 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/18 18:40:10 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{	
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		src_len;
	int		i;
	int		j;

	src_len = (ft_strlen(s1) + ft_strlen(s2));
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (src_len + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

t_node	*ft_lstnew(int fd)
{
	t_node	*elem;

	elem = (t_node *)malloc(sizeof(t_node));
	if (!elem)
		return (0);
	elem->next = NULL;
	elem->buf = malloc(1);
	if (elem->buf)
		return (0);
	elem->buf[0] = '\0';
	elem->fd = fd;
	printf("%c", elem->buf[0]);
	return (elem);
}

void	clear_all(t_node **head, int fd)
{
	t_node	*prev;
	t_node	*seek;

	prev = NULL;
	seek = *head;
	if ((*head)->fd == fd)
	{
		seek = seek->next;
		free(*head);
		(*head) = seek;
		return ;
	}
	while (seek)
	{
		if (seek->fd == fd)
		{
			prev->next = seek->next;
			free(seek);
			return ;
		}
		prev = seek;
		seek = seek->next;
	}
}
