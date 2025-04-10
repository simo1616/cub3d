/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:37:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/10 09:59:00 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->config.no_textures = NULL;
	game->config.so_textures = NULL;
	game->config.we_textures = NULL;
	game->config.ea_textures = NULL;
	game->config.color_sol[0] = -1;
	game->config.color_plafond[0] = -1;
	game->map = NULL;
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.angle = 0.0;
	game->player.movespeed = 0.0;
	game->player.rotspeed = 0.0;
	game->data_img.whith = 800;
	game->data_img.hight = 600;
}

void init_data_img(t_game *game)
{
	//couleur = (R << 16) | (G << 8) | B
	game->data_img.pixels = (int *)mlx_get_data_addr(game->img, &game->data_img.bpp,
									&game->data_img.size_line, &game->data_img.endian);
	game->data_img.size_line = game->data_img.size_line / 4;
	game->data_img.cur_color_plaf = (game->config.color_plafond[0] << 16) |
					(game->config.color_plafond[1] << 8)  |
					game->config.color_plafond[2];
	
	game->data_img.cur_color_sol = (game->config.color_sol[0] << 16) |
				(game->config.color_sol[1] << 8)  |
				game->config.color_sol[2];
	//printf("\n game->data_img.cur_color_plaf = %d\ngame->data_img.cur_color_sol = %d\n", game->data_img.cur_color_plaf, game->data_img.cur_color_sol);
}