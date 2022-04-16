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

char	*ft_freej(char *stash, char *rbuff)
{
	char	*stash_joined;

	stash_joined = ft_strjoin(stash, rbuff);
	free(stash);
	return (stash_joined);
}

char	*ft_next(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (stash[i])
		line[j++] = stash[i++];
	free(stash);
	return (line);
}

char	*ft_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] && stash[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *stash)
{
	char	*rbuff;
	int		byte_read;

	if (!stash)
		stash = ft_calloc(1, 1);
	rbuff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, rbuff, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(rbuff);
			return (NULL);
		}
		rbuff[byte_read] = 0;
		stash = ft_freej(stash, rbuff);
		if (ft_strchr(rbuff, '\n'))
			break ;
	}
	free(rbuff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_line(stash);
	stash = ft_next(stash);
	return (line);
}
