/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:37:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 14:36:20 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_textures(t_tex text[NBR_TEX])
{
	int	i;

	i = 0;
	while (i < NBR_TEX)
	{
		text[i].img = NULL;
		text[i].pixels = NULL;
		text[i].width = 0;
		text[i].height = 0;
		text[i].bpp = 0;
		text[i].size_line = 0;
		text[i].endian = 0;
		i++;
	}
}

static void	init_data_img(t_data_img *data_img)
{
	data_img->img = NULL;
	data_img->pixels = NULL;
	data_img->bpp = 0;
	data_img->size_line = 0;
	data_img->endian = 0;
}

static void	init_config(t_config *config)
{
	int	i;

	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	i = 0;
	while (i < 3)
	{
		config->floor_color[i] = -1;
		config->ceiling_color[i] = -1;
		i++;
	}
}

static void	init_player_defaults(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = -PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_structs(t_game *game)
{
	ft_memset(game, 0, sizeof(*game));
	init_data_img(&game->data_img);
	init_config(&game->config);
	game->map = NULL;
	init_player_defaults(&game->player);
	init_textures(game->textures);
}
