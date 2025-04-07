#include "cub3d.h"

void	append_map_line(t_game *game, char *cpy_line)
{
	int		i;
	int		cnt;
	char	**new_map;

	cnt = 0;
	if(game->map)
	{
		while(game->map[cnt])
			cnt++;
	}
	new_map = (char **)malloc(sizeof(char *) * (cnt + 2));
	if (!new_map)
	{
		perror("Erreur d'allocation pour la map.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	if(game->map)
	{
		while(game->map[i])
		{
			new_map[i] = game->map[i];
			i++;
		}
	}
	new_map[i] = cpy_line;
	new_map[i + 1] = NULL;
	if(game->map)
		free(game->map);
	game->map = new_map;
}
