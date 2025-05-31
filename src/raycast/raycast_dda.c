/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/05/31 18:36:20 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialise les coordonnées de la case courante 
 * et le vecteur direction du rayon.
 *
 * - map_x, map_y = case de départ (p->x/BLOCK, p->y/BLOCK).
 * - rdx = cos(ray_ang), rdy = sin(ray_ang).
 * - ddx = |1/rdx|, ddy = |1/rdy|.
 *
 * @param p Pointeur vers `t_player` (position du joueur).
 * @param ray_ang Angle du rayon en radians.
 * @param r Pointeur vers la structure `t_ray` à initialiser.
 */
static void	setup_ray(t_player *p, float ray_ang, t_ray *r)
{
	r->map_x = (int)(p->x / BLOCK);
	r->map_y = (int)(p->y / BLOCK);
	r->rdx = cosf(ray_ang);
	r->rdy = sinf(ray_ang);
	r->ddx = fabsf(1.0f / r->rdx);
	r->ddy = fabsf(1.0f / r->rdy);
}

/**
 * @brief Détermine la direction de pas (sx,sy) 
 * et les distances initiales sdx/sdy.
 *
 * - Si rdx < 0, sx = -1, sdx = (p->x/BLOCK - map_x) * ddx ; 
 * sinon sx = +1, sdx = ((map_x+1) - p->x/BLOCK) * ddx.
 * - Mêmes calculs pour rdy, sy, sdy.
 *
 * @param p Pointeur vers `t_player`.
 * @param r Pointeur vers `t_ray` 
 * contenant déjà `rdx`, `rdy`, `ddx`, `ddy`.
 */
static void	init_step(t_player *p, t_ray *r)
{
	if (r->rdx < 0)
	{
		r->sx = -1;
		r->sdx = (p->x / BLOCK - r->map_x) * r->ddx;
	}
	else
	{
		r->sx = 1;
		r->sdx = (r->map_x + 1.0f - p->x / BLOCK) * r->ddx;
	}
	if (r->rdy < 0)
	{
		r->sy = -1;
		r->sdy = (p->y / BLOCK - r->map_y) * r->ddy;
	}
	else
	{
		r->sy = 1;
		r->sdy = (r->map_y + 1.0f - p->y / BLOCK) * r->ddy;
	}
}

/**
 * @brief Exécute la boucle DDA jusqu’à toucher 
 * un mur (valeur '1' dans la map).
 *
 * - Compare sdx vs sdy pour savoir s’il faut avancer en x ou en y.
 * - Avance `map_x` ou `map_y` puis met à jour `sdx`/`sdy`.
 * - Fixe `side = 0` si on déplace en x, `side = 1` si en y.
 * - Si `map[map_y][map_x] == '1'` → stop.
 *
 * @param g Pointeur vers la structure de jeu (contient `map`).
 * @param r Pointeur vers la structure `t_ray`.
 */
static void	perform_dda(t_game *g, t_ray *r)
{
	while (true)
	{
		if (r->sdx < r->sdy)
		{
			r->sdx += r->ddx;
			r->map_x += r->sx;
			r->side = 0;
		}
		else
		{
			r->sdy += r->ddy;
			r->map_y += r->sy;
			r->side = 1;
		}
		if (g->map[r->map_y] && r->map_x >= 0
			&& r->map_x < (int)ft_strlen(g->map[r->map_y])
			&& g->map[r->map_y][r->map_x] == '1')
			break ;
	}
}

/**
 * @brief Calcule la distance perpendiculaire du joueur au mur.
 *
 * - Si `side == 0`: out[0] = (map_x - p->x/BLOCK + (1 - sx)/2) / rdx.
 * - Sinon: out[0] = (map_y - p->y/BLOCK + (1 - sy)/2) / rdy.
 * - out[1] ← `side`.
 *
 * @param p   Pointeur vers `t_player`.
 * @param r   Pointeur vers `t_ray` (côté, map_x, map_y, etc.).
 * @param out Tableau float de taille ≥ 2 :
 *            out[0] = distance perpendiculaire,
 *            out[1] = (float)side.
 */
static void	compute_perp(t_player *p, t_ray *r, float out[2])
{
	if (r->side == 0)
		out[0] = (r->map_x - p->x / BLOCK + (1 - r->sx) / 2.0f) / r->rdx;
	else
		out[0] = (r->map_y - p->y / BLOCK + (1 - r->sy) / 2.0f) / r->rdy;
	out[1] = (float)r->side;
}

/**
 * @brief Lance le raycasting DDA et renvoie la distance au mur 
 * et le côté touché.
 *
 * - Appelle `setup_ray`, `init_step`, `perform_dda`, `compute_perp`.
 * - Remplit `out[0]` (distance) et `out[1]` (side).
 *
 * @param p      Pointeur vers `t_player` (position + angle).
 * @param ray_ang Angle du rayon en radians.
 * @param g      Pointeur vers `t_game` (contient `map`).
 * @param out    Tableau float de sortie (distance + side).
 */
void	cast_ray(t_player *p, float ray_ang, t_game *g, float out[2])
{
	t_ray	r;

	setup_ray(p, ray_ang, &r);
	init_step(p, &r);
	perform_dda(g, &r);
	compute_perp(p, &r, out);
}
