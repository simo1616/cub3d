# include "cub3d.h"

int key_press(int keycode, t_game *game)
{
	printf("Touche appuyée : %d\n", keycode);
	if(keycode == 65307)
		close_window(game);
	// fleches
	else if(keycode == 65361)
		printf("Touche fleche gauche pressée\n");
	else if(keycode == 65363)
		printf("Touche fleche droite pressée\n");
	else if(keycode == 65362)
		printf("Touche fleche haut pressée\n");
	else if(keycode == 65364)
		printf("Touche fleche bas pressée\n");
	//touche clavier
	else if(keycode == 97)
		printf("Touche touche A(gauche) pressée\n");
	else if(keycode == 100)
		printf("Touche touche D(droit) pressée\n");
	else if(keycode == 119)
		printf("Touche touche W(haut) pressée\n");
	else if(keycode == 115)
		printf("Touche touche S(bas) pressée\n");
	return(0);
}
