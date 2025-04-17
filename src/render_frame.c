/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:49:00 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/16 10:57:36 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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
