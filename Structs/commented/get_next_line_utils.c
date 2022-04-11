#include "get_next_line.h"
/* Get_next_line utils, this file serves a helper functions, in this code we will reflect mostly VOID functions
this will clarify better when are we doing FREES as well as having ft_s that actually do something.*/

/* search for '\n' in last node of stash */
int	ft_found_newline(t_list *stash)
{
	int		i;
	t_list	*node_to_check;

	//first time stash = NULL --> doesnt search --> while false
	if (stash == NULL)
		return (0)
	node_to_check = ft_lst_get_last(stash);
	i = 0;
	while (node_to_check->content[i])
	{
		if (node_to_check->content[i] == '\n')
			return (1);
		i++;
	}
	return (0); // if we dont find, still add to stash
}

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list *last;

	last = stash;
	while (last && last->next)
		last = last->next;
	return (last);
}

/* most important ft_ft, we take the buffer, create a new node, and allocate the content of that at the end of list...
 but if stash == NULL -> we need to free stash and use it as first node*/
void	ft_add_to_stash(char **stash, char *rbuffer, int nbytes_r)
{
	//allocate our new_node && new_node->next = NULL -hence it is last in list
	t_list	*new_node;
	t_list	*last_node;
	int 	i;

	new_node = malloc(sizeof(t_list));
	new_node == NULL
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (nbytes_r + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (rbuffer[i] && i < nbytes_r)
	{
		new_node->content[i] = rbuffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
		*stash = new_node;
	//if stas != from NULL its not first time, then we add it at the last of our list
	last_node = ft_lst_get_last(*stash);
	last_node->next = new_node;
}

void	ft_create_line(stash, line)
{
	int	i;
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
	*line = malloc(sizeof(char) * len + 1);
	if (*line == NULL)
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
