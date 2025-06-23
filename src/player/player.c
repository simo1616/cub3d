/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:37:19 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 12:37:19 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// /**
//  * @brief Initialise la position et l’orientation du joueur.
//  *
//  * - Place le joueur au centre : (`WIDTH/2`, `HEIGHT/2`).
//  * - Angle initial = -PI/2 ; toutes les touches/mouvements à false.
//  *
//  * @param player Pointeur vers la structure `t_player`.
//  */

/**
 * @brief Gère la rotation du joueur si les flags `left_rotate` 
 * ou `right_rotate` sont actifs.
 *
 * - Si `left_rotate`, décrémente `angle` de `ROT_SPEED`.
 * - Si `right_rotate`, incrémente `angle` de `ROT_SPEED`.
 * - Normalise l’angle dans [0, 2π).
 *
 * @param player Pointeur vers la structure `t_player`.
 */
static void	rotate_player(t_player *player)
{
	if (player->left_rotate)
		player->angle -= ROT_SPEED;
	if (player->right_rotate)
		player->angle += ROT_SPEED;
	if (player->angle < 0)
		player->angle += 2 * PI;
	else if (player->angle >= 2 * PI)
		player->angle -= 2 * PI;
}

/**
 * @brief Avance/le joueur en avant ou arrière selon `key_up`/`key_down`.
 *
 * - Calcule `dir = +1` si `key_up`, `-1` si `key_down`.
 * - Calcule `new_x = x + cos(angle) * MOVE_SPEED * dir`, idem pour `new_y`.
 * - Vérifie les collisions via `is_wall`. Met à jour `player->x`/`player->y` 
 * si le déplacement est valide.
 *
 * @param player Pointeur vers la structure `t_player`.
 * @param game   Pointeur vers la structure de jeu (pour tester `is_wall`).
 */
static void	translate_player(t_player *player, t_game *game)
{
	float	new_x;
	float	new_y;
	float	dir;

	if (player->key_up || player->key_down)
	{
		if (player->key_up)
			dir = 1.0f;
		else
			dir = -1.0f;
		new_x = player->x + cosf(player->angle) * MOVE_SPEED * dir;
		new_y = player->y + sinf(player->angle) * MOVE_SPEED * dir;
		if (!is_wall(new_x, player->y, game))
			player->x = new_x;
		if (!is_wall(player->x, new_y, game))
			player->y = new_y;
	}
}

/**
 * @brief Met à jour la position et l’orientation du joueur à chaque frame.
 *
 * - Appelle `rotate_player`, `translate_player`, `strafe_player` dans cet ordre.
 *
 * @param player Pointeur vers la structure `t_player`.
 * @param game   Pointeur vers la structure de jeu (pour collisions et état).
 */
static void	strafe_player(t_player *player, t_game *game)
{
	float	new_x;
	float	new_y;
	float	dir;

	if (player->key_left || player->key_right)
	{
		if (player->key_right)
			dir = 1.0f;
		else
			dir = -1.0f;
		new_x = player->x + cosf(player->angle + dir * PI / 2) * MOVE_SPEED;
		new_y = player->y + sinf(player->angle + dir * PI / 2) * MOVE_SPEED;
		if (!is_wall(new_x, player->y, game))
			player->x = new_x;
		if (!is_wall(player->x, new_y, game))
			player->y = new_y;
	}
}

void	move_player(t_player *player, t_game *game)
{
	rotate_player(player);
	translate_player(player, game);
	strafe_player(player, game);
}
