/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:49 by jdecarro          #+#    #+#             */
/*   Updated: 2025/05/31 18:44:13 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Place un pixel de couleur donnée dans l’image MLX.
 *
 * - Si (x,y) hors écran, ne fait rien.
 * - Sinon, calcule `index = y * size_line + x` 
 * et stocke `pixels[index] = color`.
 *
 * @param x     Abscisse du pixel en pixels.
 * @param y     Ordonnée du pixel en pixels.
 * @param color Couleur 32 bits (0xAARRGGBB ou 0x00RRGGBB).
 * @param game  Pointeur vers la structure de jeu (`t_game`).
 */
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->data_img.size_line + x;
	game->data_img.pixels[index] = color;
}

/**
 * @brief Efface l’image en noir (couleur 0x00000000).
 *
 * - Parcourt tous les pixels de 0 ≤ y < HEIGHT et 0 ≤ x < WIDTH.
 * - Appelle `put_pixel(x, y, 0x00000000, game)`.
 *
 * @param game Pointeur vers la structure de jeu (`t_game`).
 */
void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0x00000000, game);
			x++;
		}
		y++;
	}
}

/**
 * @brief Dessine un carré (bord uniquement) de taille BLOCK en pixels.
 *
 * - Pour i = 0…BLOCK-1, place quatre pixels : 
 *   - (x + i, y) et (x + i, y + BLOCK) pour les bords horizontaux.
 *   - (x, y + i) et (x + BLOCK, y + i) pour les bords verticaux.
 *
 * @param x     Abscisse du coin supérieur gauche (en pixels).
 * @param y     Ordonnée du coin supérieur gauche (en pixels).
 * @param color Couleur 32 bits pour les bords.
 * @param game  Pointeur vers la structure de jeu (`t_game`).
 */
void	draw_square(int x, int y, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < BLOCK)
	{
		put_pixel(x + i, y, color, game);
		put_pixel(x + i, y + BLOCK, color, game);
		put_pixel(x, y + i, color, game);
		put_pixel(x + BLOCK, y + i, color, game);
		i++;
	}
}

/**
 * @brief Parcourt la carte et dessine un quadrillage pour les murs.
 *
 * - Pour chaque case (row,col) où `game->map[row][col] == '1'`, 
 *   appelle `draw_square(col * BLOCK, row * BLOCK, 0x0000FF, game)`.
 *
 * @param game Pointeur vers la structure de jeu (`t_game`).
 */
void	draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == '1')
				draw_square(col * BLOCK, row * BLOCK, 0x0000FF, game);
			col++;
		}
		row++;
	}
}
