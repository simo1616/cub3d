#include "cub3d.h"

int is_integer(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}

void check_access(char *trimmed, char *clean_line)
{
	int fd;

	fd = open(trimmed, O_RDONLY);
	if(fd == -1)
	{
		ft_putstr_fd("Error\nfichier de texture inaccessible: ", 2);
		ft_putstr_fd(trimmed, 2);
		free(trimmed);
		free(clean_line);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}