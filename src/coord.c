/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:24:03 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 18:03:19 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static bool	check_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}


t_player get_coord(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	if(game->map)
	{
		row = 0;
		while(game->map[row])
		{
			col = 0;
			while(game->map[col])
			{
				if(check_char(game->map[row][col]))
				{
					game->player.x = (float)row + 0.5;
					game->player.y = (float)col + 0.5;
					printf("x = %.2f, et y = %.2f\n",game->player.x, game->player.y);
					return(game->player);
				}
				col++;
			}
			row++;
		}
	}
	return(game->player);
}