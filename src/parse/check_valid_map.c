/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:41 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 13:56:49 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_borders(char **map, int height, t_parser *parser)
{
	int			row;
	t_line_info	info;

	row = 0;
	info.first = 0;
	info.last = height - 1;
	while (row < height)
	{
		info.row = row;
		check_line_borders(map[row], info, parser);
		row++;
	}
}

static void	check_and_store_player(char ch, int r, int c, t_player_data data, t_parser *parser)
{
	if (!is_valid_map_char(ch))
		error_and_exit(parser, ERR_MAP_INVALID_CHAR);
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
	{
		(*data.count)++;
		*data.row = r;
		*data.col = c;
		data.info->map2d[r][c] = '0';
	}
}

static void	validate_and_get_player(t_mapinfo *info, int *pr, int *pc, t_parser *parser)
{
	int				r;
	int				c;
	int				player_count;
	char			ch;
	t_player_data	data;

	player_count = 0;
	data.count = &player_count;
	data.row = pr;
	data.col = pc;
	data.info = info;
	r = 0;
	while (r < info->height)
	{
		c = 0;
		while (c < info->width)
		{
			ch = info->map2d[r][c];
			check_and_store_player(ch, r, c, data, parser);
			c++;
		}
		r++;
	}
	if (player_count != 1)
		error_and_exit(parser, ERR_MAP_TEXT_MORE_THAN_ONE);
}

void	check_validate_map(t_game *game, t_parser *parser)
{
	t_mapinfo	info;
	int			player_r;
	int			player_c;
	int			height;

	height = get_map_height(game->map);
	check_map_empty(height);
	check_map_borders(game->map, height, parser);
	init_mapinfo_struct(&info, game, parser);
	validate_and_get_player(&info, &player_r, &player_c, parser);
	init_visited_map(&info, parser);
	if (!dfs_closed(&info, player_r, player_c))
		error_and_exit(parser, ERR_MAP_NOT_CLOSE);
	free_mapinfo(&info);
}
