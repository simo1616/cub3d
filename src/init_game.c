/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:37:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 17:40:33 by mbendidi         ###   ########.fr       */
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
}
