/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:23 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 10:32:45 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char **map)
{
	int	cnt;

	cnt = 0;
	while (map && map[cnt])
		cnt++;
	return (cnt);
}

static char	**alloc_and_copy(char **old_map, int count)
{
	int		i;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
	{
		ft_putstr_fd(ERR_MAP_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
    DEBUG_PRINT("Allocated new_map with %d pointers at %p\n", count + 2, new_map);
#endif
	i = 0;
	while (old_map && old_map[i])
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = NULL;
	if (old_map)
		free(old_map);
#ifdef DEBUG
	DEBUG_PRINT("Freed old_map at %p\n", old_map);
#endif
	return (new_map);
}

void	append_map_line(t_game *game, char *cpy_line)
{
	int		count;
	char	**new_map;

	count = count_lines(game->map);
	new_map = alloc_and_copy(game->map, count);
	new_map[count] = cpy_line;
	new_map[count + 1] = NULL;
	// if (game->map)
	// 	free(game->map);
	game->map = new_map;
}
