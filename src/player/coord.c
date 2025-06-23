/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:24:03 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 17:01:34 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Vérifie si le caractère `c` désigne une orientation 
 * valide pour le joueur.
 *
 * - Renvoie true si `c` est 'N', 'S', 'E' ou 'W'.
 *
 * @param c Caractère à tester.
 * @return bool true si c ∈ {'N','S','E','W'}, false sinon.
 */
static bool	check_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * @brief Définit l’angle initial du joueur en fonction du caractère direction.
 *
 * - Si 'N', angle = -PI/2 ; 'S' → 3PI/2 ; 'E' → 0 ; 'W' → PI.
 *
 * @param c Caractère indiquant la direction ('N','S','E','W').
 * @param player Pointeur vers la structure `t_player` dont on met l’angle.
 */
static void	identify_char(char c, t_player *player)
{
	if (c == 'N')
		player->angle = -PI / 2;
	else if (c == 'S')
		player->angle = (PI * 3) / 2;
	else if (c == 'E')
		player->angle = 0.0;
	else if (c == 'W')
		player->angle = PI;
}

/**
 * @brief Trouve les coordonnées initiales du joueur dans la map.
 *
 * - Parcourt `game->map[row][col]` jusqu’à trouver un caractère d’orientation.
 * - Place `game->player.x = col * BLOCK + BLOCK/2`, 
 * `game->player.y = row * BLOCK + BLOCK/2`.
 * - Appelle `identify_char` pour définir `player->angle`.
 * - Retourne la structure `t_player` ainsi initialisée.
 *
 * @param game Pointeur vers la structure de jeu (contient `map` et `player`).
 * @return t_player Structure `player` mise à jour.
 */
t_player	get_coord(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	if (game->map)
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
	return (game->player);
}
