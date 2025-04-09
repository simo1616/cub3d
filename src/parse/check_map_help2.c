/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:37:02 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 16:43:13 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_visited_map(t_mapinfo *info)
{
	int	r;

	info->visited = malloc(sizeof(bool *) * info->height);
	if (!info->visited)
		error_and_exit(ERR_MAP_MALLOC);
	r = 0;
	while (r < info->height)
	{
		info->visited[r] = calloc(info->width, sizeof(bool));
		if (!info->visited[r])
			error_and_exit(ERR_MAP_MALLOC);
		r++;
	}
}

void	free_mapinfo(t_mapinfo *info)
{
	int	r;

	r = 0;
	while (r < info->height)
	{
		free(info->map2d[r]);
		free(info->visited[r]);
		r++;
	}
	free(info->map2d);
	free(info->visited);
}

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

void	check_map_empty(int height)
{
	if (height == 0)
	{
		ft_putstr_fd(ERR_MAP_EMPTY, 2);
		exit(EXIT_FAILURE);
	}
}

int	get_max_width(char **map, int height)
{
	int	i;
	int	len;
	int	width;

	width = 0;
	i = 0;
	while (i < height)
	{
		len = (int)ft_strlen(map[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}
