/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 20:28:45 by junyojeo          #+#    #+#             */
/*   Updated: 2022/08/10 20:56:18 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h>
# include <stdlib.h>

typedef struct s_node{
	struct t_node	*next;
	ssize_t			read_size;
	int				fd;
	char			buf[BUFFER_SIZE];
}	t_node;

char	*get_next_line(int fd);

#endif
