/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycas_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecarro <jdecarro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/04/30 11:03:27 by jdecarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_ray(t_player *p, float ray_ang, t_ray *r)
{
	r->map_x = (int)(p->x / BLOCK);
	r->map_y = (int)(p->y / BLOCK);
	r->rdx   = cosf(ray_ang);
	r->rdy   = sinf(ray_ang);
	r->ddx   = fabsf(1.0f / r->rdx);
	r->ddy   = fabsf(1.0f / r->rdy);
}

static void	init_step(t_player *p, t_ray *r)
{
	if (r->rdx < 0)
	{
		r->sx  = -1;
		r->sdx = (p->x / BLOCK - r->map_x) * r->ddx;
	}
	else
	{
		r->sx  = 1;
		r->sdx = (r->map_x + 1.0f - p->x / BLOCK) * r->ddx;
	}
	if (r->rdy < 0)
	{
		r->sy  = -1;
		r->sdy = (p->y / BLOCK - r->map_y) * r->ddy;
	}
	else
	{
		r->sy  = 1;
		r->sdy = (r->map_y + 1.0f - p->y / BLOCK) * r->ddy;
	}
}

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
		if (g->map[r->map_y]
		 && r->map_x >= 0
		 && r->map_x < (int)ft_strlen(g->map[r->map_y])
		 && g->map[r->map_y][r->map_x] == '1')
			break;
	}
}

static void	compute_perp( t_player *p, t_ray *r, float out[2])
{
	if (r->side == 0)
		out[0] = (r->map_x - p->x / BLOCK
				+ (1 - r->sx) / 2.0f)
				/ r->rdx;
	else
		out[0] = (r->map_y - p->y / BLOCK
				+ (1 - r->sy) / 2.0f)
				/ r->rdy;
	out[1] = (float)r->side;
}

void	cast_ray( t_player *p, float ray_ang, t_game *g, float out[2])
{
	t_ray	r;

	setup_ray(p, ray_ang, &r);
	init_step(p, &r);
	perform_dda(g, &r);
	compute_perp(p, &r, out);
}
