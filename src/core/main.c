/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:05 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:24:02 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Affiche l’utilisation du programme si 
 * le nombre d’arguments est incorrect.
 *
 * Affiche « Usage: ./cub3d <map.cub> » 
 * dans la sortie standard et retourne
 * EXIT_FAILURE.
 *
 * @return int EXIT_FAILURE toujours.
 */
static int	print_usage(void)
{
	ft_printf("Usage: ./cub3d <map.cub>\n");
	return (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_usage());
	init_structs(&game);
	if (ft_parse(&game, av[1]))
		return (EXIT_FAILURE);
	if (start_mlx(&game) == 0)
	{
		cleanup_before_exit(&game);
		return (EXIT_FAILURE);
	}
	cleanup_before_exit(&game);
	return (EXIT_SUCCESS);
}
