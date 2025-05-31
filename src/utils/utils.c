/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:51:52 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/04 12:56:09 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall_point(float px, float py, t_game *game)
{
	int		map_x;
	int		map_y;
	char	**map;
	int		row_count;

	map_x = (int)(px / BLOCK);
	map_y = (int)(py / BLOCK);
	map = game->map;
	if (map_x < 0 || map_y < 0)
		return (true);
	row_count = 0;
	while (map[row_count])
		row_count++;
	if (map_y >= row_count)
		return (true);
	if (map_x >= (int)ft_strlen(map[map_y]))
		return (true);
	return (map[map_y][map_x] == '1');
}

bool	is_wall(float px, float py, t_game *game)
{
	return (is_wall_point(px + COLLIDE_OFFSET, py + COLLIDE_OFFSET, game)
		|| is_wall_point(px - COLLIDE_OFFSET, py + COLLIDE_OFFSET, game)
		|| is_wall_point(px + COLLIDE_OFFSET, py - COLLIDE_OFFSET, game)
		|| is_wall_point(px - COLLIDE_OFFSET, py - COLLIDE_OFFSET, game));
}
