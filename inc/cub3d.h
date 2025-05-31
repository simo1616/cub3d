/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:33:13 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:55:32 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ============================= INCLUDES ============================== */
# include "../minilibx-linux/mlx.h"
# include "parser_cub3d.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

/* ============================ CONSTANTES ============================= */
/* Dimensions de la fenêtre et du buffer */
# define WIDTH            800
# define HEIGHT           600
# define IMG_W            800
# define IMG_H            600

/* Taille d'un bloc (map) et décalage collision */
# define BLOCK            64
# define COLLIDE_OFFSET   5.0f

/* Nombre de textures (NO, SO, WE, EA) */
# define NBR_TEX          4

/* Identifiants de direction pour les textures */
# define NORTH            0
# define SOUTH            1
# define WEST             2
# define EAST             3

/* Vitesse de déplacement et de rotation du joueur */
# define MOVE_SPEED       1.0f
# define ROT_SPEED        0.01f

/* Codes de touches clavier (ASCII ou X11) */
# define W                119
# define S                115
# define A                97
# define D                100
# define LEFT             65361
# define RIGHT            65363

/* Autres touches */
# define KEY_Q            113
# define KEY_ESC          65307

/* Constantes mathématiques */
# define PI               3.14159265359f
# define FOV_ANGLE_DEG    60.0f          /* Champ de vision en degrés      */
# define FOV_ANGLE_RAD    1.0471975512f  /* = 60° × PI / 180                */

/* Active ou non le mode debug (affiche slices brutes, etc.) */
# define DEBUG            0

/* ============================= STRUCTURES ============================ */

/**
 * @brief Contient l’image MLX et son buffer de pixels.
 *
 * - img       : pointeur vers l’image MLX.
 * - pixels    : tableau dynamique (int *) pointant sur les pixels.
 * - bpp       : bits par pixel.
 * - size_line : nombre d’int par ligne d’image.
 * - endian    : endianess (non utilisé explicitement).
 */
typedef struct s_data_img
{
	void	*img;
	int		*pixels;
	int		bpp;
	int		size_line;
	int		endian;
}			t_data_img;

/**
 * @brief Représente l’état du joueur.
 *
 * - x, y         : position (float) au centre du bloc.
 * - angle        : orientation en radians.
 * - key_up, key_down, key_left, key_right : flags de mouvement.
 * - left_rotate, right_rotate            : flags de rotation.
 */
typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}			t_player;

/**
 * @brief Stocke les chemins des textures et les couleurs (RGB).
 *
 * - no_texture, so_texture, we_texture, ea_texture : chemins XPM.
 * - floor_color[3], ceiling_color[3]            : valeurs R/G/B entre 0 et 255.
 */
typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}			t_config;

/**
 * @brief Contient les informations d’une texture MLX.
 *
 * - img       : pointeur vers l’image chargée.
 * - pixels    : tableau dynamique (int *) pointant sur les pixels.
 * - width     : largeur de la texture (int).
 * - height    : hauteur de la texture (int).
 * - bpp       : bits par pixel.
 * - size_line : nombre d’int par ligne de la texture.
 * - endian    : endianess de la texture (X11).
 */
typedef struct s_tex
{
	void	*img;
	int		*pixels;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}			t_tex;

/**
 * @brief Structure pour le calcul DDA du raycasting.
 *
 * - map_x, map_y    : indices de la case courante dans la map.
 * - rdx, rdy        : vecteur direction du rayon (cosθ, sinθ).
 * - ddx, ddy        : distance d'exclusion sur x, y (|1/rdx|, |1/rdy|).
 * - sdx, sdy        : distance à parcourir jusqu'au premier mur (step initial).
 * - sx, sy          : direction du pas sur x ou y (-1 ou +1).
 * - side            : 0 = mur vertical (axe x), 1 = mur horizontal (axe y).
 */
typedef struct s_ray
{
	int		map_x;
	int		map_y;
	float	rdx;
	float	rdy;
	float	ddx;
	float	ddy;
	float	sdx;
	float	sdy;
	int		sx;
	int		sy;
	int		side;
}			t_ray;

/**
 * @brief Décrit une tranche verticale à dessiner pour un mur.
 *
 * - x     : abscisse (colonne pixel) à l'écran.
 * - start : ordonnée (ligne pixel) de début.
 * - end   : ordonnée (ligne pixel) de fin.
 * - tex_x : coordonnée X dans la texture pour la slice.
 */
typedef struct s_vline
{
	int	x;
	int	start;
	int	end;
	int	tex_x;
}			t_vline;

/**
 * @brief Structure principale du jeu.
 *
 * - mlx      : contexte MLX (mlx_init).
 * - win      : pointeur de la fenêtre (mlx_new_window).
 * - map      : tableau de chaînes représentant la carte 
 * 		(char **, chaînes null-terminated).
 * - config   : configuration (textures + couleurs).
 * - player   : données du joueur (position, angle, flags).
 * - data_img : buffer d’image (MLX) pour dessiner pixel par pixel.
 * - textures : tableau de NBR_TEX textures chargées (XPM).
 */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_config	config;
	t_player	player;
	t_data_img	data_img;
	t_tex		textures[NBR_TEX];
}			t_game;

/*
** --------------------------------------------------------------------------
**   INITIALISATION & BOUCLE PRINCIPALE
** --------------------------------------------------------------------------
*/

int			start_mlx(t_game *game);
t_player	get_coord(t_game *game);

/*
** --------------------------------------------------------------------------
**   GESTION DU JOUEUR & INPUT
** --------------------------------------------------------------------------
*/

void		init_player(t_player *player);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		move_player(t_player *player, t_game *game);

/*
** --------------------------------------------------------------------------
**   GRAPHISME 2D
** --------------------------------------------------------------------------
*/

void		put_pixel(int x, int y, int color, t_game *game);
void		clear_image(t_game *game);

/*
** --------------------------------------------------------------------------
**   MINI-MAP
** --------------------------------------------------------------------------
*/

void		draw_square(int x, int y, int color, t_game *game);
void		draw_map(t_game *game);

/*
** --------------------------------------------------------------------------
**   RAYCASTING & RENDU 3D
** --------------------------------------------------------------------------
*/

void		cast_ray(t_player *p, float ray_ang, t_game *g, float out[2]);
void		draw_line(t_player *p, t_game *g, float ray_ang, int x);
int			draw_loop(t_game *g);
bool		is_wall_point(float px, float py, t_game *game);
bool		is_wall(float px, float py, t_game *game);

/*
** --------------------------------------------------------------------------
**   CHARGEMENT DES TEXTURES
** --------------------------------------------------------------------------
*/

void		text_load(t_game *game);

#endif
