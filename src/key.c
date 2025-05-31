/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:26:11 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 12:17:02 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	key_release(int keycode, t_game *game)
{
	set_player_key(keycode, &game->player, false);
	return (0);
}
