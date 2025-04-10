/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:49:00 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/10 09:10:08 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

static void init_data_img(t_game *game)
{
	game->data_img.whith = 800;
	game->data_img.hight = 600;
	game->data_img.pixels = (int *)mlx_get_data_addr(game->img, &game->data_img.bpp,
									&game->data_img.size_line, &game->data_img.endian);
	game->data_img.size_line = game->data_img.size_line / 4;
	game->data_img.cur_color_plaf = (game->config.color_plafond[0] << 16) |
					(game->config.color_plafond[1] << 8)  |
					game->config.color_plafond[2];
	game->data_img.cur_color_sol = (game->config.color_sol[0] << 16) |
				(game->config.color_sol[1] << 8)  |
				game->config.color_sol[2];	
}

void render_frame(t_game *game)
{
	int x;
	int y;

	init_data_img(game);

	y = 0;
	while(y < game->data_img.hight)
	{
		x = 0;
		while(x < game->data_img.whith)
		{
			if (y < game->data_img.hight / 2)
				game->data_img.pixels[y * game->data_img.size_line + x] = game->data_img.cur_color_plaf;
			else
				game->data_img.pixels[y * game->data_img.size_line + x] = game->data_img.cur_color_sol;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
