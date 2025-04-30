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


static bool	touch(float px, float py, t_game *game)
{
	int	x = px / BLOCK;
	int	y = py / BLOCK;
	if (x < 0 || y < 0 || !game->map[y] || game->map[y][x] != '1')
		return (false);
	return (true);
}

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

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float ray_x = player->x;
	float ray_y = player->y;
	float cos_angle = cosf(start_x);
	float sin_angle = sinf(start_x);

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		/* float dist = distance(ray_x - player->x, ray_y - player->y); */
		// controlling eye fishing effect
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 255, game);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player = &game->player;

	move_player(player);
	clear_image(game); 
	if (DEBUG)
	{
		draw_square(player->x, player->y, 20, 0x00FF00, game);
		draw_map(game);
	}
	float	fraction = PI / 3 / WIDTH;
	float	start_x = player->angle - PI / 6;
	int		i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->data_img.img, 0, 0);
	return (0);
}
