/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedraza <fpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:21:12 by fpedraza          #+#    #+#             */
/*   Updated: 2022/04/06 18:21:12 by fpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* buscamos un '\n' en nuestra lista enlazada */
int	ft_found_newline(t_list *stash)
{
	int		i;
	t_list	*node_to_check;

	if (stash == NULL)
		return (0);
	node_to_check = ft_lst_get_last(stash);
	i = 0;
	while (node_to_check->content[i])
	{
		if (node_to_check->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*return de un puntero a nuestro último nodo de nuestro stash*/
t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*last;

	last  = stash;
	while (last && last->next)
		last = last->next;
	return (last);
}

/* Add del content de nuestro buffer al final de nuestro stash*/
void	ft_add_to_stash(t_list **stash, char *buffer, int b_read)
{
	int		i;
	t_list	*last_node;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (b_read + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < b_read)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last_node = ft_lst_get_last(*stash);
	last_node->next = new_node;
}


/*calculamos numero de chars en nodos incluyendo \n y alloc a todo ello*/
void	ft_generate_line(char **line,t_list *stash)
{
	int i;
	int len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(Char) * (len + 1));
	if (line == NULL)
		return ;
}

int	ft_strlen(char *str)
{
	char *head;
	head = str;
	while (*str)
		str++;
	return (str - head);
}

/* Free toda la lista*/

void	ft_free_stash(t_list **stash)
{
	t_list	*current;
	t_list	*next;

	current = *stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
