/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/05/31 18:40:50 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Dessine la moitié supérieure (plafond) 
 * de l’écran avec une couleur donnée.
 *
 * - Parcourt y de 0 à `HEIGHT/2 - 1`, x de 0 à `WIDTH - 1`.
 * - Appelle `put_pixel(x, y, col, g)` pour chaque pixel.
 *
 * @param g   Pointeur vers la structure de jeu (`t_game`).
 * @param col Couleur 24 bits (0xRRGGBB) pour le plafond.
 */
static void	draw_ceiling(t_game *g, int col)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, col, g);
			x++;
		}
		y++;
	}
}

/**
 * @brief Dessine la moitié inférieure (sol) de l’écran avec une couleur donnée.
 *
 * - Parcourt y de `HEIGHT/2` à `HEIGHT - 1`, x de 0 à `WIDTH - 1`.
 * - Appelle `put_pixel(x, y, col, g)` pour chaque pixel.
 *
 * @param g   Pointeur vers la structure de jeu (`t_game`).
 * @param col Couleur 24 bits (0xRRGGBB) pour le sol.
 */
static void	draw_floor(t_game *g, int col)
{
	int	y;
	int	x;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, col, g);
			x++;
		}
		y++;
	}
}

/**
 * @brief Remplit le plafond et le sol de l’écran 
 * avec leurs couleurs.
 *
 * - Récupère `ceil_col` depuis `g->config.ceiling_color`.
 * - Récupère `floor_col` depuis `g->config.floor_color`.
 * - Appelle `draw_ceiling` puis `draw_floor`.
 *
 * @param g Pointeur vers la structure de jeu (`t_game`).
 */
static void	draw_floor_and_ceiling(t_game *g)
{
	int	ceil_col;
	int	floor_col;

	ceil_col = (g->config.ceiling_color[0] << 16)
		| (g->config.ceiling_color[1] << 8)
		| g->config.ceiling_color[2];
	floor_col = (g->config.floor_color[0] << 16)
		| (g->config.floor_color[1] << 8)
		| g->config.floor_color[2];
	draw_ceiling(g, ceil_col);
	draw_floor(g, floor_col);
}

/**
 * @brief Parcourt toutes les colonnes X de l’écran et appelle `draw_line`.
 *
 * - Calcule `fov = FOV_ANGLE_RAD`, `half = fov/2`.
 * - Pour chaque `i` de 0 à `WIDTH - 1`, 
 *   `ang = player.angle - half + (i * fov / WIDTH)`.
 * - Ajuste `ang` dans [0, 2π) si hors bornes.
 * - Appelle `draw_line(p, g, ang, i)`.
 *
 * @param g Pointeur vers la structure de jeu (`t_game`).
 */
static void	render_rays(t_game *g)
{
	t_player	*p;
	float		fov;
	float		half;
	int			i;
	float		ang;

	p = &g->player;
	fov = FOV_ANGLE_RAD;
	half = fov * 0.5f;
	i = 0;
	while (i < WIDTH)
	{
		ang = p->angle - half + (i * fov / (float)WIDTH);
		if (ang < 0)
			ang += 2 * PI;
		else if (ang >= 2 * PI)
			ang -= 2 * PI;
		draw_line(p, g, ang, i);
		i++;
	}
}

/**
 * @brief Boucle de rendu appelée par MLX à chaque frame.
 *
 * - Met à jour la position du joueur via `move_player`.
 * - Efface l’image (`clear_image`).
 * - Dessine le sol et le plafond (`draw_floor_and_ceiling`).
 * - Dessine tous les rayons/murs (`render_rays`).
 * - Met à jour la fenêtre MLX avec l’image (`mlx_put_image_to_window`).
 *
 * @param g Pointeur vers la structure de jeu (`t_game`).
 * @return int 0 (valeur ignorée par MLX).
 */
int	draw_loop(t_game *g)
{
	move_player(&g->player, g);
	clear_image(g);
	draw_floor_and_ceiling(g);
	render_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->data_img.img, 0, 0);
	return (0);
}
