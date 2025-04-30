#ifndef CUB3D_H
# define CUB3D_H

# include "../inc/minilibx-linux/mlx.h"
# include "parser_cub3d.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#define WIDTH 1280
#define HEIGHT 720
#define BLOCK 64
#define DEBUG 1

#define MOVE_SPEED 3.0f
#define ROT_SPEED 0.05f

# define W	122
# define S	115
# define A	113
# define D	100
# define LEFT			65361
# define RIGHT			65363

# define KEY_Q			97
# define KEY_ESC		65307

# define PI 3.14159265359

typedef struct s_data_img
{
	void *img; // mlx new image
	char *addr; // mlx get data addr

	int	bpp;
	int size_line;
	int endian;

	int	width;
	int height;
}	t_data_img;

typedef struct s_player {
    float x;
    float y;
    float angle;     // orientation 
    float movespeed; // vitesse de déplacement
    float rotspeed;  // vitesse de rotation

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;
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
	void		*mlx;
	void		*win;
	char		**map;

	t_config	config;
	t_player	player;
	t_data_img	data_img;
} t_game;


int			start_mlx(t_game *game);
t_player 	get_coord(t_game *game);
void		render_frame(t_game *game);
int loop_hook(t_game *game);

void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player);

void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
void	 draw_map(t_game *game);

void	draw_line(t_player *player, t_game *game, float start_x, int i);
int		draw_loop(t_game *game);

void 	init_structs(t_game *game);

#endif