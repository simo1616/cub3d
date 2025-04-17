/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:24:03 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/16 10:56:57 by mbendidi         ###   ########.fr       */
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
		player->angle = M_PI / 2; // 90°
	else if(c == 'S')
		player->angle = (M_PI * 3) / 2; // 270°
	else if(c == 'E')
		player->angle = 0.0; // 0°
	else if(c == 'W')
		player->angle = M_PI; // 180°
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
					game->player.x = (double)col + 0.5;
					game->player.y = (double)row + 0.5;
					identify_char(game->map[row][col], &game->player);
					game->player.movespeed = 0.1;
					game->player.rotspeed  = 0.05;
					return (game->player);
				}
				col++;
			}
			row++;
		}

	}
	return(game->player);
}