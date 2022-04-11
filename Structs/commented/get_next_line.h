#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

/*STANDAR Libraries*/
#include <unistd.h>
#include <stdio.h>
#include <fnclt.h>
#include <stdarg.h>
#include <stdlib.h>

/*If we dont define BUFFER_SIZE at compilation, we will set it at 5*/
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif /*...BUFFER_SIZE..*/

/*Since we are doing it this time with structs we need to define it, main goal is to do a linked list*/
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
} t_list;

/* get_n_line prototype and .h prototypes */

char	*get_next_line(int fd);

int		ft_found_newline(t_list *stash);

t_list	*ft_lst_get_last(t_list *stash);

void	ft_add_to_stash(char **stash, char *rbuffer, int nbytes_r);

void	ft_create_line(stash, line);

int		ft_strlen(char *str);

void	ft_free_stash(t_list **stash);

#endif /*....GET_NEXT_LINE_H....*/
