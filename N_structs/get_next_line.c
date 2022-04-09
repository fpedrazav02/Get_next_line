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
char	*ft_freej(char * stash, char *rbuff)
{
	char	*stash_join;
	stash_join = ft_strjoin(stash, rbuff);
	free(rbuff);
	return (stash_join);
}
char	*ft_read(int fd, char *stash)
{
	char	*rbuff;
	int		nbytes;

	if (!stash)
		stash = ft_calloc(1,1);
	rbuff = malloc(BUFFER_SIZE + 1 * sizeof(char));
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, rbuff, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(rbuff);
			return (NULL);
		}
		rbuff[BUFFER_SIZE] = 0;
		stash = ft_freej(stash, rbuff);
		if (ft_strchr(stash, '\n'))
			break;
	}
	free(rbuff);
	return (stash);
}

char	*ft_gline(char *stash)
{
	char	*line;
	char	eol;
	char	*start;

	start = stash;
	while (*stash && *stash != '\n')
	{
		eol++;
		stash++;
	}
	line = malloc(sizeof(char) * eol);
	while (eol--)
		*line++ = *start++;
	return (line);
}

char	*ft_clean_stash(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;

	//ERROR_HANDLING
	if (BUFFER_SIZE < 0 || fd < 0 || read (fd, 0, 0) < 0)
		return (NULL);
	stash = ft_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_gline(stash);
	stash = ft_clean_stash(stash);
	return (line);
}


