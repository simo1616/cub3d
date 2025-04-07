/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:41 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/07 20:59:51 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_borders(char **map, int height)
{
	int	row;
	int	last;

	row = 0;
	last = height - 1;
	while (row < height)
	{
		check_line_borders(map[row], row, 0, last);
		row++;
	}
}

static void	check_and_store_player(char ch, int r, int c, int *player_count, int *pr, int *pc, t_mapinfo *info)
{
	if (!is_valid_map_char(ch))
		error_and_exit(ERR_MAP_INVALID_CHAR);
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
	{
		(*player_count)++;
		*pr = r;
		*pc = c;
		info->map2d[r][c] = '0';
	}
}

static void	validate_and_get_player(t_mapinfo *info, int *pr, int *pc)
{
	int		r;
	int		c;
	int		player_count;
	char	ch;

	player_count = 0;
	r = 0;
	while (r < info->height)
	{
		c = 0;
		while (c < info->width)
		{
			ch = info->map2d[r][c];
			check_and_store_player(ch, r, c, &player_count, pr, pc, info);
			c++;
		}
		r++;
	}
	if (player_count != 1)
		error_and_exit(ERR_MAP_TEXT_MORE_THAN_ONE);
}

void	check_validate_map(t_game *game)
{
	t_mapinfo	info;
	int			player_r;
	int			player_c;
	int			height;
	int			width;

	height = get_map_height(game->map);
	check_map_empty(height);
	check_map_borders(game->map, height);
	width = get_max_width(game->map, height);
	init_mapinfo_struct(&info, game->map, height, width);
	validate_and_get_player(&info, &player_r, &player_c);
	init_visited_map(&info);
	if (!dfs_closed(&info, player_r, player_c))
		error_and_exit(ERR_MAP_NOT_CLOSE);
	free_mapinfo(&info);
}
