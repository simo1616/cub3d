#ifndef CUB3D_H
# define CUB3D_H


# include "parser_cub3d.h"
# include <math.h>

# define NBR 4
# define WIDTH 800
# define HEIGHT 600
# define WIDTH_IMG 800
# define HEIGHT_IMG 600

typedef struct s_data_img
{
	int	bpp;
	int size_line;
	int endian;
	int *pixels;
	int cur_color_plaf; 
	int cur_color_sol;
}	t_data_img;

typedef struct s_player {
    double x;
    double y;
    double angle;// orientation 
    double movespeed; // vitesse de déplacement
    double rotspeed;  // vitesse de rotation
} t_player;

typedef struct s_config {
	char	*no_textures;
	char	*so_textures;
	char	*we_textures;
	char	*ea_textures;
	int		color_sol[3];
	int		color_plafond[3];
} t_config;

typedef struct s_tex
{
	void	*img;
	int		*pixels;
	int		width;
	int		height;
	int		bpp;
	int		size_line;  // en int pixels
	int		endian;
} t_tex;

typedef struct s_game {
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	t_config	config;
	t_player	player;
	t_data_img	data_img;
	t_tex		textures[NBR];
} t_game;




int			start_mlx(t_game *game);
t_player 	get_coord(t_game *game);
void		render_frame(t_game *game);
void		init_data_img(t_game *game);
int			loop_hook(t_game *game);
void		text_load(t_game *g, t_tex tex[NBR]);
uint32_t	tex_get(const t_tex *tex, int hor, int ver);

#endif