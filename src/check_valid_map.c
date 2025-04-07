/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:41 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/07 19:28:32 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

static void	check_map_empty(int height)
{
	if (height == 0)
	{
		ft_putstr_fd("Error\nMap vide.\n", 2);
		exit(EXIT_FAILURE);
	}
}

static int	get_max_width(char **map, int height)
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

static void	init_mapinfo_struct(t_mapinfo *info, char **map, int h, int w)
{
	int	r;
	int	c;
	int	len;

	info->height = h;
	info->width = w;
	info->map2d = malloc(sizeof(char *) * h);
	if (!info->map2d)
		exit_msg("Error\nMalloc failed for map2d.\n");
	r = -1;
	while (++r < h)
	{
		info->map2d[r] = malloc(sizeof(char) * (w + 1));
		if (!info->map2d[r])
			exit_msg("Error\nMalloc failed for map2d row.\n");
		len = (int)ft_strlen(map[r]);
		c = -1;
		while (++c < len)
			info->map2d[r][c] = map[r][c];
		while (c < w)
			info->map2d[r][c++] = ' ';
		info->map2d[r][w] = '\0';
	}
}

static void	validate_and_get_player(t_mapinfo *info, int *pr, int *pc)
{
	int		r;
	int		c;
	int		player_count;
	char	ch;

	player_count = 0;
	r = -1;
	while (++r < info->height)
	{
		c = -1;
		while (++c < info->width)
		{
			ch = info->map2d[r][c];
			if (!is_valid_map_char(ch))
				exit_msg("Error\nCaractère invalide.\n");
			if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
			{
				player_count++;
				*pr = r;
				*pc = c;
				info->map2d[r][c] = '0';
			}
		}
	}
	if (player_count != 1)
		exit_msg("Error\nIl faut exactement 1 orientation (N,S,E,W).\n");
}

static void	init_visited_map(t_mapinfo *info)
{
	int	r;

	info->visited = malloc(sizeof(bool *) * info->height);
	if (!info->visited)
		exit_msg("Error\nMalloc failed for visited.\n");
	r = -1;
	while (++r < info->height)
	{
		info->visited[r] = calloc(info->width, sizeof(bool));
		if (!info->visited[r])
			exit_msg("Error\nMalloc failed for visited row.\n");
	}
}

static void	free_mapinfo(t_mapinfo *info)
{
	int	r;

	r = -1;
	while (++r < info->height)
	{
		free(info->map2d[r]);
		free(info->visited[r]);
	}
	free(info->map2d);
	free(info->visited);
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
		exit_msg("Error\nMap non fermée (fuite détectée)\n");
	free_mapinfo(&info);
}
