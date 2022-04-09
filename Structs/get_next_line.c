/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedraza <fpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:21:18 by fpedraza          #+#    #+#             */
/*   Updated: 2022/04/06 18:21:18 by fpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Usar read para meter el buffer en nuetro stash */

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	int				b_read;

	stash = NULL;
	line = NULL;
	b_read = 1;
	//ERROR HANDLING
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &line, 0) < 0)
		return (NULL);
	//1 --> leer del FD y meter el buffer al stash
	ft_read_and_stash(&stash, &b_read, fd);
	if (stash == NULL)
		return (NULL);
	ft_get_line(stash, &line);
	ft_clean_stash(&stash);
	if (line[0] == '\0')
	{
		ft_free_stash(&stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* Usaremos la función read() para añadir los charcs del buffer de read al stash */
void	ft_read_and_stash(t_list **stash, int *b_read_ptr, int fd)
{
	char *buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return ;
	while ((!ft_found_newline(*stash) && *b_read_ptr != 0))
	{
		*b_read_ptr = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*stash == NULL && *b_read_ptr == 0) || *b_read_ptr == -1)
		{
			free(buffer);
			return ;
		}
		buffer[*b_read_ptr] =) '\0';
		ft_add_to_stash(*stash, buffer, *b_read_ptr);
		free(buffer);
	}
}

/*extraer los chars de todos nuestros nodos, parando si encuentra un '\n' */
void	ft_get_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	ft_generate_line(line, stash);
	if (*line == NULL)
		return ;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}


/* Una vez hemos sacado la línea, no necesitamos ya los chars de la lista, así que necesitamos limpiar la lista,
excepto los chars que no hemos sacado en nuestra función de get_line */
void	ft_clean_stash(t_list	**stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node-> next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * (ft_strlen(last->content) - i + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
	{
		clean_node->content[j++] = last->content[i++];
	}
	clean_node->content[j] = '\0';
	ft_free_stash(&stash);
	*stash = clean_node;
}
