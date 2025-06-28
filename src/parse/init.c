/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:59 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/27 21:48:08 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Copie la chaîne `src` dans `dest` 
 * et complète par espaces jusqu’à `width`.
 *
 * - Calcule `len = strlen(src)`.
 * - Copie caractère par caractère `src` dans `dest`.
 * - Remplit `dest[len..width-1]` avec des espaces.
 * - Met `dest[width] = '\0'`.
 *
 * @param dest Chaîne déjà allouée de longueur ≥ width+1.
 * @param src  Chaîne source (une ligne de map).
 * @param width Largeur cible (colonnes) pour le padding.
 */
void	copy_and_pad_line(char *dest, char *src, int width)
{
	int	len;
	int	c;

	len = (int)ft_strlen(src);
	c = 0;
	while (c < len)
	{
		dest[c] = src[c];
		c++;
	}
	while (c < width)
	{
		dest[c] = ' ';
		c++;
	}
	dest[width] = '\0';
}

static void	cleanup_and_exit(t_mapinfo *info, int rows, t_parser *parser)
{
	while (--rows >= 0)
		free(info->map2d[rows]);
	free(info->map2d);
	error_and_exit(parser, ERR_MAP_MALLOC);
}

static void	alloc_map_rows(t_game *g, t_mapinfo *info, t_parser *parser)
{
	int	r;

	r = 0;
	while (r < info->height)
	{
		info->map2d[r] = malloc(sizeof(char) * (info->width + 1));
		if (!info->map2d[r])
			cleanup_and_exit(info, r, parser);
		copy_and_pad_line(info->map2d[r], g->map[r], info->width);
		r++;
	}
}

/**
 * @brief Initialise une structure `t_mapinfo` à partir de `game->map`.
 *
 * - `h = get_map_height(game->map)`, `w = get_max_width(game->map, h)`.
 * - `info->height = h`, `info->width = w`.
 * - Alloue `info->map2d = malloc(sizeof(char*) * h)`.
 * - Pour chaque ligne r ∈ [0..h-1] :
 *   - Alloue `info->map2d[r] = malloc(sizeof(char) * (w + 1))`.
 *   - Si échec, `error_and_exit(parser, ERR_MAP_MALLOC)`.
 *   - Appelle `copy_and_pad_line(info->map2d[r], game->map[r], w)`.
 *
 * @param info   Pointeur vers `t_mapinfo` à initialiser.
 * @param game   Pointeur vers la structure de jeu (`t_game`), contient `map`.
 * @param parser Pointeur vers la structure `t_parser` pour gérer les erreurs.
 */
void	init_mapinfo_struct(t_mapinfo *info, t_game *game, t_parser *parser)
{
	int	h;
	int	w;

	h = get_map_height(game->map);
	w = get_max_width(game->map, h);
	info->height = h;
	info->width = w;
	info->map2d = malloc(sizeof(char *) * h);
	if (!info->map2d)
		error_and_exit(parser, ERR_MAP_MALLOC);
	alloc_map_rows(game, info, parser);
}

/**
 * @brief Initialise la structure `t_parser` pour démarrer le parsing.
 *
 * - Met `match_text`, `match_color`, `map_started`, 
 * `map_is_done`, `empty_line_after_map` à false.
 * - Met `line`, `clean_line`, `trimmed` à NULL.
 * - Stocke `parser->game = game`.
 * - Alloue `parser->state = malloc(sizeof(t_cleanup_state))` et, si OK, 
 *   met `state->game_cleaned = false` et `state->parser_cleaned = false`.
 *
 * @param parser Pointeur vers `t_parser` à initialiser.
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 */
void	init_parser(t_parser *parser, t_game *game)
{
	ft_memset(parser, 0, sizeof(t_parser));
	parser->match_text = 0;
	parser->match_color = 0;
	parser->map_started = false;
	parser->map_is_done = false;
	parser->config_complete = false;
	parser->empty_line_after_map = false;
	parser->line = NULL;
	parser->clean_line = NULL;
	parser->trimmed = NULL;
	parser->game = game;
	parser->state = malloc(sizeof(t_cleanup_state));
	if (parser->state)
	{
		parser->state->game_cleaned = false;
		parser->state->parser_cleaned = false;
		parser->state->mapinfo = NULL;
	}
}
