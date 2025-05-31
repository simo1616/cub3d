/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:41 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 14:13:12 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ---------- 1) Bordures de la carte -------------------------------------- */
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

/* ---------- 2) Traitement d’un caractère --------------------------------- */
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

/* Parcourt toute la map pour trouver le joueur */
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

/* ---------- 3) Validation : un seul joueur ------------------------------- */
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

/* ---------- 4) Fonction principale --------------------------------------- */
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
