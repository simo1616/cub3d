/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:41 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:20:51 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Vérifie que chaque ligne de la carte est bordée par des murs.
 *
 * - Pour row ∈ [0..h-1], initialise 
 * `inf.first = 0`, `inf.last = h-1`, `inf.row = row`.
 * - Appelle `check_line_borders(map[row], inf, parser)` 
 * pour vérifier chaque bord.
 *
 * @param map Tableau de chaînes représentant la map 2D.
 * @param h   Hauteur de la map (nombre de lignes).
 * @param p   Pointeur vers la structure `t_parser`.
 */
static void	check_map_borders(char **map, int h, t_parser *p)
{
	int			row;
	t_line_info	inf;

	row = 0;
	inf.first = 0;
	inf.last = h - 1;
	while (row < h)
	{
		inf.row = row;
		check_line_borders(map[row], inf, p);
		row++;
	}
}

/**
 * @brief Traite un caractère `ch` de la map pour compter le joueur éventuel.
 *
 * - Si `ch` invalide (pas '0'/'1'/'N'/'S'/'E'/'W'/' '), 
 * appelle `error_and_exit`.
 * - Si `ch ∈ {'N','S','E','W'}` : 
 * incrémente `*d->count`, stocke `*d->row = r`, `*d->col = c`,
 *   remplace `info->map2d[r][c]` par '0'.
 *
 * @param ch Caractère courant dans la map.
 * @param r  Ligne courante (index).
 * @param c  Colonne courante (index).
 * @param d  Pointeur vers `t_player_data` 
 * (contient count, row, col, info, parser).
 */
static void	store_player(char ch, int r, int c, t_player_data *d)
{
	if (!is_valid_map_char(ch))
		error_and_exit(d->parser, ERR_MAP_INVALID_CHAR);
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
	{
		(*d->count)++;
		*d->row = r;
		*d->col = c;
		d->info->map2d[r][c] = '0';
	}
}

/**
 * @brief Parcourt toute la map 2D pour trouver un caractère de joueur.
 *
 * - Pour r ∈ [0..info->height-1], c ∈ [0..info->width-1]:
 *   - Appelle `store_player(info->map2d[r][c], r, c, d)`.
 *
 * @param info Pointeur vers `t_mapinfo` (contient `map2d`, `height`, `width`).
 * @param d    Pointeur vers `t_player_data` 
 * (contient count/row/col/info/parser).
 */
static void	scan_map_for_player(t_mapinfo *info, t_player_data *d)
{
	int		r;
	int		c;
	char	ch;

	r = 0;
	while (r < info->height)
	{
		c = 0;
		while (c < info->width)
		{
			ch = info->map2d[r][c];
			store_player(ch, r, c, d);
			c++;
		}
		r++;
	}
}

/**
 * @brief Valide qu’il y a exactement un joueur dans la map.
 *
 * - Initialise `player_cnt = 0`.
 * - Prépare `d.count = &player_cnt`, 
 * 		`d.row = pr`, `d.col = pc`, `d.info = info`, `d.parser = p`.
 * - Appelle `scan_map_for_player(info, &d)`.
 * - Si `player_cnt != 1`, 
 * 		appelle `error_and_exit(p, ERR_MAP_TEXT_MORE_THAN_ONE)`.
 *
 * @param info Pointeur vers `t_mapinfo` (contient la carte pad).
 * @param pr   Pointeur vers un entier où stocker la ligne du joueur.
 * @param pc   Pointeur vers un entier où stocker la colonne du joueur.
 * @param p    Pointeur vers la structure `t_parser`.
 */
static void	validate_and_get_player(t_mapinfo *info, int *pr,
			int *pc, t_parser *p)
{
	t_player_data	d;
	int				player_cnt;

	player_cnt = 0;
	d.count = &player_cnt;
	d.row = pr;
	d.col = pc;
	d.info = info;
	d.parser = p;
	scan_map_for_player(info, &d);
	if (player_cnt != 1)
		error_and_exit(p, ERR_MAP_TEXT_MORE_THAN_ONE);
}

/**
 * @brief Exécute la validation complète de la map et libère `info`.
 *
 * - `height = get_map_height(game->map)`.
 * - `check_map_empty(height)`.
 * - `check_map_borders(game->map, height, p)`.
 * - `init_mapinfo_struct(&info, game, p)`.
 * - `validate_and_get_player(&info, &player_r, &player_c, p)`.
 * - `init_visited_map(&info, p)`.
 * - Si `!dfs_closed(&info, player_r, player_c)`, 
 * appelle `error_and_exit(p, ERR_MAP_NOT_CLOSE)`.
 * - `free_mapinfo(&info)`.
 *
 * @param g Pointeur vers la structure de jeu (`t_game`).
 * @param p Pointeur vers la structure `t_parser`.
 */
void	check_validate_map(t_game *g, t_parser *p)
{
	t_mapinfo	info;
	int			player_r;
	int			player_c;
	int			height;

	height = get_map_height(g->map);
	check_map_empty(height);
	check_map_borders(g->map, height, p);
	init_mapinfo_struct(&info, g, p);
	validate_and_get_player(&info, &player_r, &player_c, p);
	init_visited_map(&info, p);
	if (!dfs_closed(&info, player_r, player_c))
		error_and_exit(p, ERR_MAP_NOT_CLOSE);
	free_mapinfo(&info);
}
