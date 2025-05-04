/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:26:11 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/04 18:15:06 by mbendidi         ###   ########.fr       */
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
		p->left_rotate  = state;
	else if (keycode == RIGHT)
		p->right_rotate = state;
	else if ((keycode == KEY_ESC || keycode == KEY_Q) && state)
		exit(0);
}

int key_press(int keycode, t_player *player)
{
	set_player_key(keycode, player, true);
	return (0);
}

int key_release(int keycode, t_player *player)
{
	set_player_key(keycode, player, false);
	return (0);
}
