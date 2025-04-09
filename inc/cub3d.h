#ifndef CUB3D_H
# define CUB3D_H


# include "parser_cub3d.h"
# include <math.h>

//# define M_PI 3.14159265f
typedef struct s_player {
    float x;
    float y;
    float angle;     // orientation du regard
    float movespeed; // vitesse de déplacement
    float rotspeed;  // vitesse de rotation
} t_player;
typedef struct s_config {
	char	*no_textures;
	char	*so_textures;
	char	*we_textures;
	char	*ea_textures;
	int		color_sol[3];
	int		color_plafond[3];
} t_config;

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*img;
	char	**map;
	t_config config;
	t_player  player;
} t_game;


int			start_mlx(t_game *game);
t_player 	get_coord(t_game *game);

#endif