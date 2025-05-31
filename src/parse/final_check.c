/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:19:21 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 11:23:13 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_textures(t_game *game, t_parser *parser)
{
	if (!game->config.no_texture)
		error_and_exit(parser, ERR_TEXTURE_NOT_DEFINED_NO);
	if (!game->config.so_texture)
		error_and_exit(parser, ERR_TEXTURE_NOT_DEFINED_SO);
	if (!game->config.ea_texture)
		error_and_exit(parser, ERR_TEXTURE_NOT_DEFINED_EA);
	if (!game->config.we_texture)
		error_and_exit(parser, ERR_TEXTURE_NOT_DEFINED_WE);
}

static void	check_colors(t_game *game, t_parser *parser)
{
	if (game->config.floor_color[0] == -1)
		error_and_exit(parser, ERR_COLOR_NOT_DEFINED_F);
	if (game->config.ceiling_color[0] == -1)
		error_and_exit(parser, ERR_COLOR_NOT_DEFINED_C);
}

static void	check_map_presence(t_game *game, t_parser *parser)
{
	if (!game->map)
		error_and_exit(parser, ERR_MAP_NOT_DEFINED);
}

void	final_check_config(t_game *game, t_parser *parser)
{
	if (!game)
		return ;
	check_textures(game, parser);
	check_colors(game, parser);
	check_map_presence(game, parser);
}
