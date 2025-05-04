/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:24:03 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/04 18:44:51 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static bool	check_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	identify_char(char c, t_player *player)
{
	if(c == 'N')
		player->angle = -PI / 2; // 90°
	else if(c == 'S')
		player->angle = (PI * 3) / 2; // 270°
	else if(c == 'E')
		player->angle = 0.0; // 0°
	else if(c == 'W')
		player->angle = PI; // 180°
}

t_player get_coord(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	if(game->map)
	{
		while (game->map[row] != NULL)
		{
			col = 0;
			while (game->map[row][col] != '\0')
			{
				if (check_char(game->map[row][col]))
				{
					game->player.x = col * BLOCK + BLOCK / 2.0f;
					game->player.y = row * BLOCK + BLOCK / 2.0f;
					identify_char(game->map[row][col], &game->player);
					return (game->player);
				}
				col++;
			}
			row++;
		}

	}
	return(game->player);
}