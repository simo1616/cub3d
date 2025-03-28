# include "cub3d.h"

void	free_split(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}