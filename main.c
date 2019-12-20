#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
	int		fd;
	char	*line;
	int		r;

	fd = open("test.txt", O_RDONLY);
	r = get_next_line(fd, &line);
	printf("%d %s \n", r, line);
	r = get_next_line(fd, &line);
	printf("%d %s \n", r, line);
	r = get_next_line(fd, &line);
	printf("%d %s \n", r, line);
	r = get_next_line(fd, &line);
	printf("%d %s \n", r, line);
	return 0;
}