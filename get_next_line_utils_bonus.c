/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:20:08 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/22 02:32:34 by junyojeo         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	s_len = ft_strlen(s);
	// if (start >= s_len)
	// 	return (ft_strdup(""));
	i = 0;
	while (s[start + i] && i < len)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = -1;
	while (len-- && s[start + (++i)])
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		src_len;
	int		i;
	int		j;

	src_len = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)malloc(sizeof(char) * (src_len + 1));
	if (!str)
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
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
	elem->buf = NULL;
	elem->buf = malloc(1);
	if (!elem->buf)
		return (0);
	elem->buf[0] = '\0';
	elem->fd = fd;
	return (elem);
}

void	clear_all(t_node *head, int fd, char *buf)
{
	t_node	*prev;

	if (buf)
		free(buf);
	prev = head;
	head = head->next;
	while (head)
	{
		if (head->fd == fd)
		{
			prev->next = head->next;
			free(head);
			return ;
		}
		prev = head;
		head = head->next;
	}
}

