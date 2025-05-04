/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/05/04 15:20:17 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Trace une tranche verticale texturée à l'écran.
*/
static void	draw_vertical_line(t_vline v, t_game *g, t_tex *tex)
{
	int		line_height;
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;

	line_height = v.end - v.start + 1;
	step = (float)tex->height / line_height;
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

static float	compute_hit( t_player *p, float perp_dist, float ray_ang, int side)
{
	float hit;

	if (side == 0)
		hit = p->y + sinf(ray_ang) * perp_dist * BLOCK;
	else
		hit = p->x + cosf(ray_ang) * perp_dist * BLOCK;
	return (hit);
}

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

static void	draw_slice(int x, t_game *g, float out[2], float ray_ang)
{
	float			perp_dist;
	int				draw_start;
	int				draw_end;
	t_tex			*tex;
	int				tex_x;
	t_vline			v;

	perp_dist = out[0];
	draw_start = (HEIGHT - (int)(DIST_PROJ_PLANE / perp_dist)) / 2;
	draw_end = draw_start + (int)(DIST_PROJ_PLANE / perp_dist);
	tex = select_texture(g, (int)out[1], ray_ang);
	tex_x = (int)(
		fmodf(compute_hit(&g->player, perp_dist,
			ray_ang, (int)out[1]),
		BLOCK)
		/ BLOCK * tex->width
	);

	v.x = x;
	v.start = draw_start;
	v.end = draw_end;
	v.tex_x = tex_x;
	draw_vertical_line(v, g, tex);
}

void	draw_line(t_player *p, t_game *g, float ray_ang, int x)
{
	float	out[2];

	cast_ray(p, ray_ang, g, out);

	if (!DEBUG)
	draw_slice(x, g, out, ray_ang);
}