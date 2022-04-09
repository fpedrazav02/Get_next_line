#include "get_next_line.h"
#include <stdio.h>
int main ()
{
	int n;

	char	*ptr;
	n = open("test.txt", "r");
	read (n, ptr, 5);
	return (0);
}
