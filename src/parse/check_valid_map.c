/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:41 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/28 14:02:01 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
static void	validate_and_get_player(t_mapinfo *info, int *pr, int *pc,
		t_parser *p)
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
	{
		free_mapinfo(info);
		if (p && p->state)
			p->state->mapinfo = NULL;
		error_and_exit(p, ERR_MAP_TEXT_MORE_THAN_ONE);
	}
}

/**
 * @brief Calcule la largeur minimale de toutes les lignes de la map.
 *
 * @param map    Tableau de chaînes représentant la map 2D.
 * @param height Hauteur de la map (nombre de lignes).
 * @return       Largeur minimale trouvée.
 */
static int	get_min_width(char **map, int height)
{
	int	min_width;
	int	i;
	int	len;

	min_width = 999;
	i = 0;
	while (i < height && map[i])
	{
		len = ft_strlen(map[i]);
		if (len < min_width)
			min_width = len;
		i++;
	}
	return (min_width);
}

/**
 * @brief Valide le joueur et vérifie que la map est fermée.
 *
 * - `validate_and_get_player(&info, &player_r, &player_c, p)`.
 * - `init_visited_map(&info, p)`.
 * - Si `!dfs_closed(&info, player_r, player_c)`,
 *   appelle `error_and_exit(p, ERR_MAP_NOT_CLOSE)`.
 * - `free_mapinfo(&info)`.
 *
 * @param info Pointeur vers `t_mapinfo` (structure initialisée).
 * @param p    Pointeur vers la structure `t_parser`.
 */
static void	validate_player_and_close(t_mapinfo *info, t_parser *p)
{
	int	player_r;
	int	player_c;

	validate_and_get_player(info, &player_r, &player_c, p);
	init_visited_map(info, p);
	if (!dfs_closed(info, player_r, player_c))
	{
		free_mapinfo(info);
		if (p && p->state)
			p->state->mapinfo = NULL;
		error_and_exit(p, ERR_MAP_NOT_CLOSE);
	}
	free_mapinfo(info);
	if (p && p->state)
		p->state->mapinfo = NULL;
}

/**
 * @brief Exécute la validation complète de la map.
 *
 * - Vérifie la taille minimale et les bordures.
 * - Initialise la structure mapinfo.
 * - Délègue la validation du joueur et DFS à validate_player_and_close.
 *
 * @param g Pointeur vers la structure de jeu (`t_game`).
 * @param p Pointeur vers la structure `t_parser`.
 */
void	check_validate_map(t_game *g, t_parser *p)
{
	t_mapinfo	info;
	int			height;
	int			min_width;

	ft_memset(&info, 0, sizeof(t_mapinfo));
	height = get_map_height(g->map);
	check_map_empty(height);
	if (height < 3)
		error_and_exit(p, ERR_MAP_TOO_SMALL);
	min_width = get_min_width(g->map, height);
	if (min_width < 3)
		error_and_exit(p, ERR_MAP_TOO_SMALL);
	check_map_borders(g->map, height, p);
	init_mapinfo_struct(&info, g, p);
	if (p && p->state)
		p->state->mapinfo = &info;
	validate_player_and_close(&info, p);
}
