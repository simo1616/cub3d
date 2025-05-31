/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:48 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:24:33 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gère la fermeture de la fenêtre MLX et termine l’application.
 *
 * - Détruit la fenêtre (mlx_destroy_window).
 * - Détruit l’affichage MLX (mlx_destroy_display).
 * - Libère le contexte `game->mlx`.
 * - Appelle `exit(0)` pour quitter immédiatement.
 *
 * @param game Pointeur vers la structure de jeu (contient contextes MLX).
 * @return int Valeur ignorée (appel à exit() en interne).
 */
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
