/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:19:25 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 16:12:15 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cub3d.h"

int	key_press(int keycode, t_game *game)
{
	printf("Touche appuyée : %d\n", keycode);
	if (keycode == 65307)
		close_window(game);
	else if (keycode == 65361)
		printf("Touche fleche gauche pressée\n");
	else if (keycode == 65363)
		printf("Touche fleche droite pressée\n");
	else if (keycode == 65362)
		printf("Touche fleche haut pressée\n");
	else if (keycode == 65364)
		printf("Touche fleche bas pressée\n");
	else if (keycode == 97)
		printf("Touche touche A(gauche) pressée\n");
	else if (keycode == 100)
		printf("Touche touche D(droit) pressée\n");
	else if (keycode == 119)
		printf("Touche touche W(haut) pressée\n");
	else if (keycode == 115)
		printf("Touche touche S(bas) pressée\n");
	return (0);
}
