/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:37:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 13:39:56 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initialise les textures à NULL ou 0.
*/
static void	init_textures(t_tex textures[NBR_TEX])
{
	int	i;

	i = 0;
	while (i < NBR_TEX)
	{
		textures[i].img = NULL;
		textures[i].pixels = NULL;
		textures[i].width = 0;
		textures[i].height = 0;
		textures[i].bpp = 0;
		textures[i].size_line = 0;
		textures[i].endian = 0;
		i++;
	}
}

void	init_structs(t_game *game)
{
	int	i;

	i = 0;
	ft_memset(game, 0, sizeof(*game));
	game->mlx = NULL;
	game->win = NULL;
	game->data_img.img = NULL;
	game->data_img.pixels = NULL;
	game->data_img.bpp = 0;
	game->data_img.size_line = 0;
	game->data_img.endian = 0;
	game->config.no_texture = NULL;
	game->config.so_texture = NULL;
	game->config.we_texture = NULL;
	game->config.ea_texture = NULL;
	while (i < 3)
	{
		game->config.floor_color[i] = -1;
		game->config.ceiling_color[i] = -1;
		i++;
	}
	game->map = NULL;
	game->player.x = WIDTH / 2;
	game->player.y = HEIGHT / 2;
	game->player.angle = -PI / 2;
	game->player.key_up = false;
	game->player.key_down = false;
	game->player.key_left = false;
	game->player.key_right = false;
	game->player.left_rotate = false;
	game->player.right_rotate = false;
	init_textures(game->textures);
}
