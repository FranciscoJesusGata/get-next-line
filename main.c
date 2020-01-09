#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
	int		fd;
	int		i;
	int		j;
	char    *line = 0;
	char	*lineadress[66];

	j = 1;
	if (!(fd = open("alphabet", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		lineadress[j - 1] = line;
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	return(0);
}