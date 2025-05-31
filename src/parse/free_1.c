/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:56 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:29:20 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Libère toutes les ressources allouées dans `parser` 
 * (mais pas `parser` lui-même).
 *
 * - Si `parser == NULL`, ne fait rien.
 * - Si `parser->line != NULL`, free(line), met `line = NULL`.
 * - Si `parser->clean_line != NULL`, free(clean_line), met `clean_line = NULL`.
 * - Si `parser->trimmed != NULL`, free(trimmed), met `trimmed = NULL`.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	cleanup_parser_resources(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->line)
	{
		free(parser->line);
		parser->line = NULL;
	}
	if (parser->clean_line)
	{
		free(parser->clean_line);
		parser->clean_line = NULL;
	}
	if (parser->trimmed != NULL)
	{
		free(parser->trimmed);
		parser->trimmed = NULL;
	}
}

/**
 * @brief Libère un tableau de chaînes `map` et chaque chaîne à l’intérieur.
 *
 * - Si `map == NULL`, ne fait rien.
 * - Sinon, pour chaque `map[i] != NULL`, free(map[i]).
 * - Puis free(map).
 *
 * @param map Tableau de chaînes (map) à libérer.
 */
void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/**
 * @brief Libère tous les chemins de texture stockés dans `t_config`.
 *
 * - Si `config == NULL`, ne fait rien.
 * - Si `config->no_texture != NULL`, free, 
 * idem pour `so_texture`, `we_texture`, `ea_texture`.
 * - Met tous les champs `*_texture = NULL`.
 *
 * @param config Pointeur vers la structure `t_config`.
 */
void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->ea_texture)
	{
		free(config->ea_texture);
	}
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
}

/**
 * @brief Libère toutes les ressources du parsing *et* de la map dans `game`.
 *
 * - Si `game` et `parser` et `parser->state` et `!parser->state->game_cleaned` :
 *   - Met `parser->state->game_cleaned = true`.
 *   - `free_config(&game->config)`.
 *   - Si `game->map != NULL`, `free_map(game->map)`, met `game->map = NULL`.
 * - Si `parser` et `parser->state` et `!parser->state->parser_cleaned` :
 *   - Met `parser->state->parser_cleaned = true`.
 *   - `parser->trimmed = NULL`.
 *   - Appelle `cleanup_parser_resources(parser)`.
 * - Si `parser` et `parser->state` :
 *   - `free(parser->state)`, `parser->state = NULL`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	cleanup_all(t_game *game, t_parser *parser)
{
	if (game && parser && parser->state && !parser->state->game_cleaned)
	{
		parser->state->game_cleaned = true;
		free_config(&game->config);
		if (game->map)
		{
			free_map(game->map);
			game->map = NULL;
		}
	}
	if (parser && parser->state && !parser->state->parser_cleaned)
	{
		parser->state->parser_cleaned = true;
		parser->trimmed = NULL;
		cleanup_parser_resources(parser);
	}
	if (parser && parser->state)
	{
		free(parser->state);
		parser->state = NULL;
	}
}

/**
 * @brief Libère les ressources du jeu juste avant la sortie.
 *
 * - `free_config(&game->config)`.
 * - `free_map(game->map)`.
 * - Si `game->mlx != NULL` et `game->win != NULL`, appelle `mlx_destroy_window`.
 *
 * @param game Pointeur vers la structure de jeu (`t_game`).
 */
void	cleanup_before_exit(t_game *game)
{
	free_config(&game->config);
	free_map(game->map);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
}
