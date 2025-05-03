/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecarro <jdecarro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:27 by jdecarro          #+#    #+#             */
/*   Updated: 2025/04/30 11:03:27 by jdecarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool	touch(float px, float py, t_game *game)
// {
// 	int	x = px / BLOCK;
// 	int	y = py / BLOCK;
// 	if (x < 0 || y < 0 || !game->map[y] || game->map[y][x] != '1')
// 		return (false);
// 	return (true);
// }

static float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

static float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

static void draw_vertical_line(int x, int draw_start, int draw_end, const t_tex *tex, int tex_x, t_game *game)
{
	int   line_height = draw_end - draw_start + 1;
	float step        = (float)tex->height / line_height;
	float tex_pos     = 0.0f;

	if (draw_start < 0)
	{
		tex_pos    = -draw_start * step;
		draw_start = 0;
	}
	for (int y = draw_start; y <= draw_end && y < HEIGHT; y++)
	{
		int tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		int color = tex->pixels[tex_y * tex->size_line + tex_x];
		put_pixel(x, y, color, game);
	}
}

static void	cast_ray(t_player *player, float start_x, t_game *game, float coords[4])
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	ray_x     = player->x;
	ray_y     = player->y;
	cos_angle = cosf(start_x);
	sin_angle = sinf(start_x);

	while (!is_wall(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	coords[0] = ray_x;
	coords[1] = ray_y;
	coords[2] = cos_angle;
	coords[3] = sin_angle;
}

static void	draw_slice(int i, t_player *player,
	t_game *game, float coords[4])
{
	float		dist;
	float		height;
	int			start_y;
	float		hit_pos;
	const t_tex	*tex;

	dist     = fixed_dist(player->x, player->y,
		coords[0], coords[1], game);
	height   = (BLOCK / dist) * (WIDTH / 2);
	start_y  = (HEIGHT - height) / 2;

	if (fabsf(coords[2]) > fabsf(coords[3]))
	{
		hit_pos = fmodf(coords[1], BLOCK) / (float)BLOCK;
		if (coords[2] > 0)
			tex = &game->textures[SOUTH];
		else
			tex = &game->textures[NORTH];
	}
	else
	{
		hit_pos = fmodf(coords[0], BLOCK) / (float)BLOCK;
		if (coords[3] > 0)
			tex = &game->textures[EAST];
		else
			tex = &game->textures[WEST];
	}

	draw_vertical_line(i, start_y,
		start_y + height,
		tex,
		(int)(hit_pos * tex->width),
		game);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	coords[4];

	cast_ray(player, start_x, game, coords);

	if (!DEBUG)
		draw_slice(i, player, game, coords);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fov;
	float		half_fov;
	float		ray_angle;
	int			i;

	player = &game->player;
	fov = FOV_ANGLE; // 60°
	half_fov = fov * 0.5f; // 30°
	i = 0;
	move_player(&game->player, game);
	clear_image(game); 
	if (DEBUG)
	{
		draw_square(player->x, player->y, 20, 0x00FF00, game);
		draw_map(game);
	}
	// float	fraction = PI / 3 / WIDTH;
	// float	start_x = player->angle - PI / 6;
	// int		i = 0;
	while (i < WIDTH)
	{
		ray_angle = player->angle - half_fov + ((float)i * fov / (float)WIDTH);
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		else if (ray_angle >= 2 * PI)
			ray_angle -= 2 * PI;
		draw_line(player, game, ray_angle, i);
		//cast_single_ray(player, game, ray_angle, i);
		//start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->data_img.img, 0, 0);
	return (0);
}
