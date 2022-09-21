/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:20:08 by junyojeo          #+#    #+#             */
/*   Updated: 2022/09/22 06:13:30 by junyojeo         ###   ########.fr       */
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
	if (start >= s_len)
	{
		str = malloc(1);
		return (str);
	}
	i = 0;
	while (s[start + i] && i < len)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = -1;
	while (++i < len && s[start + i])
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

	if (s1)
		s1 = "";
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

t_node	*ft_lstnew(int fd, t_node *node, t_node *prev)
{
	t_node	*elem;

	elem = (t_node *)malloc(sizeof(t_node));
	if (!elem)
		return (0);
	prev->next = elem;
	elem->next = NULL;
	elem->buf = NULL;
	elem->fd = fd;
	return (elem);
}

void	remove_fd(int fd, t_node *node)
{
	t_node	*prev;

	while (node)
	{
		if (fd == node->fd)
		{
			prev->next = node->next;
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}

