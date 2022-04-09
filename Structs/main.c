
#include "get_next_line.h"

#include <fcntl.h>

int main ()
{
	char	*line;
	int		fd;

	fd = fopen("test.txt", 0_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line = NULL)
			break ;
		printf("La linea es: %s", line);
		free(line);
	}
	return (0);
}
