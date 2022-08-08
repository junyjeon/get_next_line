#ifndef GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#ifndef	BUFFER_SIZE
#define	BUFFER_SIZE	1048576
typedef struct s_backup
{
	int		fd;
	char	buf[BUFFER_SIZE];
}	t_backup;
#else
# if BUFFER_SIZE < 1
#  ERROR BUFFER_SIZE is too small
# endif
#endif

#endif
