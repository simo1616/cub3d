/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:26 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 12:36:26 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Assigne la texture NO (Nord) si elle n’est pas déjà définie.
 *
 * - Vérifie via `assign_if_not_defined` que `game->config.no_texture` est vide.
 * - Si la chaîne `parser->trimmed` est valide, 
 * la duplique et la stocke dans `game->config.no_texture`.
 * - Sinon, `assign_if_not_defined` gère l’erreur (message + cleanup + exit).
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser` 
 * (contient `trimmed` et les infos d’erreur).
 */
static void	assign_no(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.no_texture, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_NO, parser);
}

/**
 * @brief Assigne la texture SO (Sud) si elle n’est pas déjà définie.
 *
 * - Vérifie via `assign_if_not_defined` que `game->config.so_texture` est vide.
 * - Duplique `parser->trimmed` et stocke dans `game->config.so_texture`.
 * - Sinon, gère l’erreur.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	assign_so(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.so_texture, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_SO, parser);
}

/**
 * @brief Assigne la texture WE (Ouest) si elle n’est pas déjà définie.
 *
 * - Vérifie via `assign_if_not_defined` que `game->config.we_texture` est vide.
 * - Duplique `parser->trimmed` et stocke dans `game->config.we_texture`.
 * - Sinon, gère l’erreur.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	assign_we(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.we_texture, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_WE, parser);
}

/**
 * @brief Assigne la texture EA (Est) si elle n’est pas déjà définie.
 *
 * - Vérifie via `assign_if_not_defined` que `game->config.ea_texture` est vide.
 * - Duplique `parser->trimmed` et stocke dans `game->config.ea_texture`.
 * - Sinon, gère l’erreur.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	assign_ea(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.ea_texture, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_EA, parser);
}

/**
 * @brief Assigne la texture NO/​SO/​WE/​EA selon la ligne lue.
 *
 * - Si `clean_line` commence par "NO ", appelle `assign_no(game, parser)`.
 * - Sinon si "SO ", appelle `assign_so`.
 * - Sinon si "WE ", appelle `assign_we`.
 * - Sinon si "EA ", appelle `assign_ea`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	assign_texture(t_game *game, t_parser *parser)
{
	if (!ft_strncmp(parser->clean_line, "NO ", 3))
		assign_no(game, parser);
	else if (!ft_strncmp(parser->clean_line, "SO ", 3))
		assign_so(game, parser);
	else if (!ft_strncmp(parser->clean_line, "WE ", 3))
		assign_we(game, parser);
	else if (!ft_strncmp(parser->clean_line, "EA ", 3))
		assign_ea(game, parser);
}
