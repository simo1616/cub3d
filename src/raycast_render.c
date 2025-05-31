/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/05/31 12:32:05 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	render_rays(t_game *g)
{
	t_player	*p;
	float		fov;
	float		half;
	int			i;
	float		ang;

	p = &g->player;
	fov = FOV_ANGLE;
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

int	draw_loop(t_game *g)
{
	move_player(&g->player, g);
	clear_image(g);
	draw_floor_and_ceiling(g);
	render_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->data_img.img, 0, 0);
	return (0);
}
