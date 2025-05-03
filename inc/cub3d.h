/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:33:13 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/03 11:40:49 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "parser_cub3d.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define IMG_W 800
#define IMG_H 600
#define BLOCK 64
#define DEBUG 0
#define COLLIDE_OFFSET 5.0f

#define MOVE_SPEED 3.0f
#define ROT_SPEED 0.05f

# define W	119 //122
# define S	 115//115
# define A	97//113
# define D	100//100
# define LEFT			65361
# define RIGHT			65363

# define KEY_Q			113//97
# define KEY_ESC		65307

# define PI 3.14159265359
# define FOV_ANGLE   (60.0f * (PI / 180.0f))

typedef struct s_data_img
{
	void	*img;
	//char	*addr;
	int		*pixels;
	int		bpp;
	int		size_line;
	int		endian;
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
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;

	int		floor_color[3];
	int		ceiling_color[3];
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

void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void 	move_player(t_player *player, t_game *game);

void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
void	draw_square(int x, int y, int size, int color, t_game *game);
void	 draw_map(t_game *game);

void	draw_line(t_player *player, t_game *game, float start_x, int i);
int		draw_loop(t_game *game);

void 	init_structs(t_game *game);
bool 	is_wall(float px, float py, t_game *g);


#endif