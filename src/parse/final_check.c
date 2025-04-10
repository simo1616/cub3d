/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:19:21 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 16:41:16 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_textures(t_game *game)
{
	if (!game->config.no_textures)
		error_and_exit(ERR_TEXTURE_NOT_DEFINED_NO);
	if (!game->config.so_textures)
		error_and_exit(ERR_TEXTURE_NOT_DEFINED_SO);
	if (!game->config.ea_textures)
		error_and_exit(ERR_TEXTURE_NOT_DEFINED_EA);
	if (!game->config.we_textures)
		error_and_exit(ERR_TEXTURE_NOT_DEFINED_WE);
}

static void	check_colors(t_game *game)
{
	if (game->config.color_sol[0] == -1)
		error_and_exit(ERR_COLOR_NOT_DEFINED_F);
	if (game->config.color_plafond[0] == -1)
		error_and_exit(ERR_COLOR_NOT_DEFINED_C);
}

static void	check_map_presence(t_game *game)
{
	if (!game->map)
		error_and_exit(ERR_MAP_NOT_DEFINED);
}

void	final_check_config(t_game *game)
{
	if (!game)
		return ;
	check_textures(game);
	check_colors(game);
	check_map_presence(game);
}
