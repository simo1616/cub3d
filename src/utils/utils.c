/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:51:52 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:46:36 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Vérifie si un point (px,py) tombe sur un mur (‘1’) dans la map.
 *
 * - Calcule `map_x = (int)(px/BLOCK)`, `map_y = (int)(py/BLOCK)`.
 * - Si `map_x < 0` ou `map_y < 0` ou `map_y >= nombre_de_lignes`, renvoie true.
 * - Si `map_x >= longueur_de_la_ligne`, renvoie true.
 * - Sinon, renvoie `(map[map_y][map_x] == '1')`.
 *
 * @param px   Coordonnée X (float) du point en pixels.
 * @param py   Coordonnée Y (float) du point en pixels.
 * @param game Pointeur vers la structure de jeu (`t_game`).
 * @return bool true si le point est sur un mur ou hors-carte, false sinon.
 */
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

/**
 * @brief Vérifie si une collision se produit en un point proche de (px,py).
 *
 * - Teste 4 coins autour : 
 *   (px ± COLLIDE_OFFSET, py ± COLLIDE_OFFSET).
 * - Si l’un des quatre coins est sur un mur (via `is_wall_point`), renvoie true.
 *
 * @param px   Coordonnée X (float) du point central.
 * @param py   Coordonnée Y (float) du point central.
 * @param game Pointeur vers la structure de jeu (`t_game`).
 * @return bool true si collision détectée, false sinon.
 */
bool	is_wall(float px, float py, t_game *game)
{
	return (is_wall_point(px + COLLIDE_OFFSET, py + COLLIDE_OFFSET, game)
		|| is_wall_point(px - COLLIDE_OFFSET, py + COLLIDE_OFFSET, game)
		|| is_wall_point(px + COLLIDE_OFFSET, py - COLLIDE_OFFSET, game)
		|| is_wall_point(px - COLLIDE_OFFSET, py - COLLIDE_OFFSET, game));
}
