/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedraza <fpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 04:09:29 by fpedraza          #+#    #+#             */
/*   Updated: 2022/04/16 04:09:29 by fpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>

int	main(void)
{
	FILE	*fp;
	char	*line;
	int		fd;
	int		n_linea;

	n_linea = 0;
	fp = fopen("test.txt", "r");
	fd = fileno(fp);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("La linea es %d: %s", n_linea, line);
		free(line);
		n_linea++;
	}
	return (0);
}
