/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecarro <jdecarro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:37:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/02 11:22:01 by jdecarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	init_config_game(t_game *game)
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
} */

void init_structs(t_game *game)
{
    int i;

    game->mlx = NULL;
    game->win = NULL;

    game->data_img.img      = NULL;
    game->data_img.addr     = NULL;
    game->data_img.bpp      = 0;
    game->data_img.size_line = 0;
    game->data_img.endian   = 0;
    game->data_img.width    = WIDTH;
    game->data_img.height   = HEIGHT;

    game->config.no_texture = NULL;
    game->config.so_texture = NULL;
    game->config.we_texture = NULL;
    game->config.ea_texture = NULL;

    // Couleurs : on initialise TOUT le tableau à -1
    for (i = 0; i < 3; i++)
    {
        game->config.floor_color[i]   = -1;
        game->config.ceiling_color[i] = -1;
    }

    game->map = NULL;

    game->player.x = WIDTH / 2;
    game->player.y = HEIGHT / 2;
    game->player.angle = -PI / 2;
    game->player.movespeed = MOVE_SPEED;
    game->player.rotspeed = ROT_SPEED;

	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
}

