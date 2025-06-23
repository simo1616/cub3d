/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/06/23 18:19:50 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Trace une ligne verticale texturée à l’écran pour une slice de mur.
 *
 * - Calcule `step = (float)tex->height / (v.end - v.start + 1)`.
 * - Si `v.start < 0`, décale `tex_pos` et met `v.start = 0`.
 * - Vérifie `v.tex_x` (bornes entre 0 et `tex->width - 1`).
 * - Pour `y` de `v.start` à `v.end` (et < HEIGHT), 
 * 	 calcule `tex_y = (int)tex_pos & (tex->height - 1)`,
 *   incrémente `tex_pos` de `step`, 
 * 	 puis appelle `put_pixel(v.x, y, couleur, g)`.
 *
 * @param v   Structure `t_vline` définissant `x`, `start`, `end`, `tex_x`.
 * @param g   Pointeur vers `t_game` (pour accès à `data_img`).
 * @param tex Pointeur vers la texture (`t_tex`) utilisée pour cette slice.
 */
static void	draw_vertical_line(t_vline v, t_game *g, t_tex *tex)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;

	step = (float)tex->height / (v.end - v.start + 1);
	tex_pos = 0.0f;
	if (v.start < 0)
	{
		tex_pos = -v.start * step;
		v.start = 0;
	}
	if (v.tex_x < 0)
		v.tex_x = 0;
	else if (v.tex_x >= tex->width)
		v.tex_x = tex->width - 1;
	y = v.start;
	while (y <= v.end && y < HEIGHT)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		put_pixel(v.x, y++, tex->pixels[tex_y * tex->width + v.tex_x], g);
	}
}

/**
 * @brief Sélectionne la bonne texture selon le côté touché par le rayon.
 *
 * - Si `side == 0` (mur vertical) : si `cos(ray_ang) > 0` → EAST, sinon WEST.
 * - Si `side == 1` (mur horizontal) : 
 * si `sin(ray_ang) > 0` → SOUTH, sinon NORTH.
 *
 * @param g       Pointeur vers la structure de jeu (contient `textures[]`).
 * @param side    0 = mur vertical, 1 = mur horizontal.
 * @param ray_ang Angle du rayon en radians.
 * @return t_tex* Pointeur vers la texture correspondante.
 */
static t_tex	*select_texture(t_game *g, int side, float ray_ang)
{
	if (side == 0)
	{
		if (cosf(ray_ang) > 0)
			return (&g->textures[EAST]);
		else
			return (&g->textures[WEST]);
	}
	else
	{
		if (sinf(ray_ang) > 0)
			return (&g->textures[SOUTH]);
		else
			return (&g->textures[NORTH]);
	}
}

/**
 * @brief Calcule la coordonnée `hit` sur le mur (entre 0 et BLOCK).
 *
 * - Si `side == 0` : renvoie `p->y + sin(ray_ang) * perp_dist * BLOCK`.
 * - Sinon : renvoie `p->x + cos(ray_ang) * perp_dist * BLOCK`.
 *
 * @param p        Pointeur vers `t_player` (position du joueur).
 * @param perp_dist Distance perpendiculaire renvoyée par DDA.
 * @param ray_ang  Angle du rayon en radians.
 * @param side     0 ou 1 (côté touché).
 * @return float Valeur de la coordonnée d’impact sur le mur (en unités de jeu).
 */
static float	compute_hit(t_player *p, float perp_dist, float ray_ang,
		int side)
{
	if (side == 0)
		return (p->y + sinf(ray_ang) * perp_dist * BLOCK);
	else
		return (p->x + cosf(ray_ang) * perp_dist * BLOCK);
}

/**
 * @brief Dessine une slice verticale en appelant `draw_vertical_line`.
 *
 * - Calcule `proj_plane = (WIDTH/2) / tan(FOV_ANGLE_RAD/2)`.
 * - `v.start = (HEIGHT - (int)(proj_plane / perp_dist)) / 2`.
 * - `v.end = v.start + (int)(proj_plane / perp_dist)`.
 * - `v.x = x`.
 * - `tex = select_texture(...)`.
 * - `v.tex_x = (int)(fmod(compute_perp_hit(...)/BLOCK) * tex->width)`.
 * - Appelle `draw_vertical_line(v, g, tex)`.
 *
 * @param x       Abscisse de la slice à l’écran (colonne pixel).
 * @param g       Pointeur vers la structure de jeu.
 * @param out     Tableau float où out[0] = distance, out[1] = side.
 * @param ray_ang Angle du rayon en radians.
 */
static void	draw_slice(int x, t_game *g, float out[2], float ray_ang)
{
	float	perp_dist;
	float	proj_plane;
	t_tex	*tex;
	t_vline	v;

	perp_dist = out[0];
	proj_plane = (WIDTH / 2.0f) / tanf(FOV_ANGLE_RAD * 0.5f);
	v.start = (HEIGHT - (int)(proj_plane / perp_dist)) / 2;
	v.end = v.start + (int)(proj_plane / perp_dist);
	v.x = x;
	tex = select_texture(g, (int)out[1], ray_ang);
	v.tex_x = (int)(fmodf(compute_hit(&g->player, perp_dist, ray_ang,
					(int)out[1]), BLOCK) / BLOCK * tex->width);
	if ((int)out[1] == 0 && cosf(ray_ang) < 0)
		v.tex_x = tex->width - v.tex_x - 1;
	else if ((int)out[1] == 1 && sinf(ray_ang) > 0)
		v.tex_x = tex->width - v.tex_x - 1;
	draw_vertical_line(v, g, tex);
}

/**
 * @brief Lance le dessin d’une tranche au pixel horizontal `x`.
 *
 * - Appelle `cast_ray`, récupère `out[2]` (distance + side).
 * - Si DEBUG == 0, appelle `draw_slice(x, g, out, ray_ang)`.
 *
 * @param p      Pointeur vers `t_player` (position + angle).
 * @param g      Pointeur vers `t_game`.
 * @param ray_ang Angle du rayon en radians.
 * @param x      Abscisse de la colonne à dessiner.
 */
void	draw_line(t_player *p, t_game *g, float ray_ang, int x)
{
	float	out[2];

	cast_ray(p, ray_ang, g, out);
	if (!DEBUG)
		draw_slice(x, g, out, ray_ang);
}
