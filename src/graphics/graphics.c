/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:03:49 by jdecarro          #+#    #+#             */
/*   Updated: 2025/07/02 12:03:02 by mbendidi         ###   ########.fr       */
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
