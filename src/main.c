#include "cub3d.h"


void	print_debug(t_game *game)
{
	int i = 0;
	printf("---------- Debug Configuration ----------\n");
	printf("Textures :\n");
	printf("  NO: %s\n", game->config.no_textures);
	printf("  SO: %s\n", game->config.so_textures);
	printf("  WE: %s\n", game->config.we_textures);
	printf("  EA: %s\n", game->config.ea_textures);
	printf("Couleurs :\n");
	printf("  Sol      : %d, %d, %d\n",
		game->config.color_sol[0],
		game->config.color_sol[1],
		game->config.color_sol[2]);
	printf("  Plafond  : %d, %d, %d\n",
		game->config.color_plafond[0],
		game->config.color_plafond[1],
		game->config.color_plafond[2]);
	printf("-----------------------------------------\n");
	printf("-------map--------\n");
	while(game->map[i])
	{
		printf("%s\n", game->map[i]);
		i++;
	}
	printf("-----------------------------------------\n");
}

int main(int ac, char **av) 
{
	if (ac != 2) 
	{
		printf("Usage: ./cub3d map.cub\n");
		return (1);
	}

	t_game	game;
	init_config_game(&game);
	if (ft_parse(&game, av[1]))
		return(1);
	print_debug(&game);
	game.mlx = mlx_init();
	if (!game.mlx) 
	{
		printf("Erreur : Init mlx\n");
		return (1);
	}
	game.win = mlx_new_window(game.mlx, 800, 600, "Cube3D");
	if (!game.win) 
	{
		printf("Erreur : new_window\n");
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return (1);
	}
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
