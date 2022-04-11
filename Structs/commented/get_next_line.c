#include "get_next_line.h"

//READ DOCUMENTATION
/*
	ssize_t read(int fd, void *buf, size_t count);
	Return values;
	0 --> indicates end of file
	>0 && <= BUFFER_SIZE (count) --> number of characters read
	-1 --> ERROR
*/

/*
	1) define our return --> a line in this case, we need to be careful of files with no endline.
	2) probably best to use static variables, in this case a static linked list
	3) create the linked list, and everytime we create a new node, check its content... if it has a
		'\n' end there.
	4) get the line cleaned somehow from our linked list
	5) clear our stash --> maybe our node has aaaaa\naaa, we need to clear stash for next usage.
	n_bytes read --> actually really important...
		1) we can use it to stop it if read has reached 0
		2)if we have a B_SIZE of a 1000 and we can only copy 3 chars we should not waste our memory on mallocing
			our nodes content...
*/
char	*get_next_line(int fd)
{
	int				nbytes_r;
	char			*line;
	static t_list	*stash;

	nbytes_r = 1;
	line = NULL;
	stash = NULL;
	//ERROR HANDLING
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	//1 -> read file and create our linked list, up until read = 0 or buffer has '\n'
	ft_read_and_stash(&stash, fd, nbytes_r);
	//2 -> extract line
	ft_get_new_line(stash, &line);
	//3 --> clean stash
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

/*Create a linked list and stash reads buffer until read = 0 or checks it the last node created has '\n'*/
void	ft_read_and_stash(t_list **stash, int fd, int *nbytes_r_ptr)
{
	//need a buffer to get content from read
	char	*rbuff;
	//alloc rbuffer and check
	rbuff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (rbuff == NULL)
		return ;
	//we are trying to add to a node in stash while our node doesnt have '\n' or read == 0
	//while false
	while ((!ft_found_newline(*stash)) && *nbytes_r_ptr != 0)
	{
		*nbytes_r_ptr = (int)read(fd, rbuff, BUFFER_SIZE);
		if (*nbytes_r_ptr == -1 || (*stash == NULL && *nbytes_r_ptr == 0))
		{
			free(rbuff);
			return ;
		}
		rbuff[*nbytes_r_ptr] = '\0';
		//we have buffer, we get it while checking for errors, if they happen then free rbuff, free of stash later
		// add buffers content to stash...
		ft_add_to_stash(*stash, rbuff, *nbytes_r_ptr);
		free(rbuff);
	}
}

void	ft_get_new_line(t_list *stash, char **line)
{
	int		i;
	int		j;

	if (stash == NULL)
		return ;
	//calculate and create spaces for our final line... use other ft_util
	ft_create_line(stash, line);
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

/* Once created our linked list the next thing we actaully need to do is clean our linked list*/
void	ft_clean_stash (t_list **stash)
{
	int		i;
	int		j;
	t_list	*new_stash;
	t_list	*last;

	new_stash = malloc(sizeof(t_list));
	if (new_stash == NULL || *stash == NULL)
		return ;
	last = ft_lst_get_last(t_list *stash);
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] == '\n')
		i++;
	new_stash->content = malloc(sizeof(char)* (ft_strlen(last->content) - i +1));
	if (new_stash->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		new_stash->content[j++] = last->content[i++];
	new_stash->content[i] = '\0';
	ft_free_stash(&stash);
	*stash = new_stash;
}
