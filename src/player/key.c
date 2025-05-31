/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:26:11 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:30:51 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Met à jour l’état d’une touche de déplacement/rétrécissement.
 *
 * - Si keycode == W/S/A/D/LEFT/RIGHT, modifie respectivement
 *   `p->key_up`, `p->key_down`, `p->key_left`, `p->key_right`,
 *   `p->left_rotate`, `p->right_rotate` à `state`.
 *
 * @param keycode Code de la touche reçue par MLX.
 * @param p Pointeur vers la structure `t_player`.
 * @param state true si la touche est pressée, false si relâchée.
 */
static void	set_player_key(int keycode, t_player *p, bool state)
{
	if (keycode == W)
		p->key_up = state;
	else if (keycode == S)
		p->key_down = state;
	else if (keycode == A)
		p->key_left = state;
	else if (keycode == D)
		p->key_right = state;
	else if (keycode == LEFT)
		p->left_rotate = state;
	else if (keycode == RIGHT)
		p->right_rotate = state;
}

/**
 * @brief Callback MLX lors de l’appui d’une touche.
 *
 * - Si ESC ou Q, appelle `cleanup_before_exit` et `exit(EXIT_SUCCESS)`.
 * - Sinon, appelle `set_player_key` pour mettre `p->key_* = true`.
 *
 * @param keycode Code de la touche pressée.
 * @param game Pointeur vers la structure de jeu (contient `t_player`).
 * @return int 0 (valeur ignorée par MLX).
 */
int	key_press(int keycode, t_game *game)
{
	if ((keycode == KEY_ESC || keycode == KEY_Q))
	{
		cleanup_before_exit(game);
		exit(EXIT_SUCCESS);
	}
	set_player_key(keycode, &game->player, true);
	return (0);
}

/**
 * @brief Callback MLX lors du relâchement d’une touche.
 *
 * - Appelle `set_player_key` pour mettre `p->key_* = false`.
 *
 * @param keycode Code de la touche relâchée.
 * @param game Pointeur vers la structure de jeu (contient `t_player`).
 * @return int 0 (valeur ignorée par MLX).
 */
int	key_release(int keycode, t_game *game)
{
	set_player_key(keycode, &game->player, false);
	return (0);
}
