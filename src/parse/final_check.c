/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:19:21 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:04:37 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Vérifie que toutes 
 * les textures (NO, SO, EA, WE) sont définies.
 *
 * - Si `game->config.no_texture == NULL`, 
 * appelle `error_and_exit(parser, ERR_TEXTURE_NOT_DEFINED_NO)`.
 * - Idem pour SO, EA, WE avec leurs macros d’erreur respectives.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
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

/**
 * @brief Vérifie que les couleurs du sol (F) 
 * et du plafond (C) sont définies.
 *
 * - Si `game->config.floor_color[0] == -1`, 
 * appelle `error_and_exit(parser, ERR_COLOR_NOT_DEFINED_F)`.
 * - Si `game->config.ceiling_color[0] == -1`, 
 * appelle `error_and_exit(parser, ERR_COLOR_NOT_DEFINED_C)`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	check_colors(t_game *game, t_parser *parser)
{
	if (game->config.floor_color[0] == -1)
		error_and_exit(parser, ERR_COLOR_NOT_DEFINED_F);
	if (game->config.ceiling_color[0] == -1)
		error_and_exit(parser, ERR_COLOR_NOT_DEFINED_C);
}

/**
 * @brief Vérifie qu’une map a bien été lue (`game->map != NULL`).
 *
 * - Si la map n’existe pas, 
 * appelle `error_and_exit(parser, ERR_MAP_NOT_DEFINED)`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	check_map_presence(t_game *game, t_parser *parser)
{
	if (!game->map)
		error_and_exit(parser, ERR_MAP_NOT_DEFINED);
}

/**
 * @brief Effectue les vérifications finales après parsing des éléments.
 *
 * - Appelle `check_textures`, `check_colors`, `check_map_presence`.
 * - Ne fait rien si `game == NULL`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	final_check_config(t_game *game, t_parser *parser)
{
	if (!game)
		return ;
	check_textures(game, parser);
	check_colors(game, parser);
	check_map_presence(game, parser);
}
