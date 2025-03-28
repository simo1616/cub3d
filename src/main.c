# include "cub3d.h"


int main ()
{
	t_game game;

	game.mlx = mlx_init();
	if(!game.mlx)
	{
		printf("Erreur : Init mlx");
		return (1);
	}
	game.win = mlx_new_window(game.mlx, 800, 600, "Cube3D");
	if (!game.win)
	{
		printf("Erreur : new_window");
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return (1);
	}
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_loop(game.mlx);
	return(0);
}
