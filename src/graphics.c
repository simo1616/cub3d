/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecarro <jdecarro@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:49 by jdecarro          #+#    #+#             */
/*   Updated: 2025/04/30 11:03:49 by jdecarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	index = y * game->data_img.size_line + x; //* (game->data_img.bpp / 8);
	// game->data_img.addr[index] = color & 0xFF;
	// game->data_img.addr[index + 1] = (color >> 8) & 0xFF;
	// game->data_img.addr[index + 2] = (color >> 16) & 0xFF;
	game->data_img.pixels[index] = color;
}

void	clear_image(t_game *game)
{
	int	y = 0;
	int	x = 0;

	for(y = 0; y < HEIGHT; y++)
		for(x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0x00000000, game);
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
	{
		put_pixel(x + i, y, color, game);
		put_pixel(x + i, y + size, color, game);
		put_pixel(x, y + i, color, game);
		put_pixel(x + size, y + i, color, game);
	}
}

/* void	draw_map(t_game *game)
{
	char	**map = game->map;
	int		color = 0x0000FF;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
} */

// Affiche les murs de la map en petits carrés
void draw_map(t_game *game)
{
	for (int row = 0; game->map[row]; row++)
		for (int col = 0; game->map[row][col]; col++)
			if (game->map[row][col] == '1')
				draw_square(col * BLOCK, row * BLOCK, BLOCK, 0x0000FF, game);
}
