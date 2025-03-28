#ifndef CUB3D
# define CUB3D


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <libft.h>


typedef struct s_game
{
	void	*mlx;
	void	*win;
} t_game;



int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);












#endif