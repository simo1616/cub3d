#ifndef CUB3D_H
# define CUB3D_H


#include "parser_cub3d.h"


typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*img;
	char	**map;
	t_config config;
} t_game;



int			handle_mlx(t_game *game);

#endif