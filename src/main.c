/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:05 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/30 17:09:27 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	print_debug(t_game *game)
{
	int	i;

	i = 0;
	printf("---------- Debug Configuration ----------\n");
	printf("Textures :\n");
	printf("  NO: %s\n", game->config.no_textures);
	printf("  SO: %s\n", game->config.so_textures);
	printf("  WE: %s\n", game->config.we_textures);
	printf("  EA: %s\n", game->config.ea_textures);
	printf("Couleurs :\n");
	printf("  Sol      : %d, %d, %d\n", game->config.color_sol[0],
		game->config.color_sol[1], game->config.color_sol[2]);
	printf("  Plafond  : %d, %d, %d\n", game->config.color_plafond[0],
		game->config.color_plafond[1], game->config.color_plafond[2]);
	printf("-----------------------------------------\n");
	printf("-------map--------\n");
	while (game->map[i])
	{
		printf("%s\n", game->map[i]);
		i++;
	}
	printf("-----------------------------------------\n");
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Usage: ./cub3d map.cub\n");
		return (EXIT_FAILURE);
	}
	init_config_game(&game);
	if (ft_parse(&game, av[1]))
		return (EXIT_FAILURE);
	//print_debug(&game);
	if(start_mlx(&game))
		return (EXIT_FAILURE);
	cleanup_before_exit(&game);
	return (EXIT_SUCCESS);
} */

static int  print_usage(void)
{
	ft_printf("Usage: ./cub3d <map.cub>\n");
	return (EXIT_FAILURE);
}

int main(int ac, char **av)
{
	t_game game;

	printf("[1] Après déclaration de game\n");
	if (ac != 2)
		return (print_usage());
	printf("[2] Après init_config_game\n");
	init_structs(&game);
	if (ft_parse(&game, av[1]))
		return (EXIT_FAILURE);
	printf("[3] Après parsing, map chargée\n");
	/* if (DEBUG)
		print_debug(&game); */
	printf("[4] Avant start_mlx\n");
	if (start_mlx(&game) == 0)
	{
		cleanup_before_exit(&game);
		return (EXIT_FAILURE);
	}
	printf("[5] Après start_mlx (ça ne devrait jamais s’afficher avant exit)\n");
	cleanup_before_exit(&game);
	return (EXIT_SUCCESS);
}
