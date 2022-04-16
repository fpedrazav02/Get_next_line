/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedraza <fpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:20:50 by fpedraza          #+#    #+#             */
/*   Updated: 2022/04/06 18:20:50 by fpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 5
// #endif /*...BUFFER_SIZE...*/

char	*get_next_line(int fd);

void	*ft_calloc(size_t nitems, size_t size);

void	ft_bzero(void *s, size_t n);

char	*ft_strjoin(char *s1, char *s2);

int		ft_strlen(char *str);

char	*ft_strchr(char const *original_str, int char_to_search);
#endif /*....GET_NEXT_LINE_H...*/
