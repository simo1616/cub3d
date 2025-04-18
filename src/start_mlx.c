/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:10:47 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/17 19:30:33 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int loop_hook(t_game *game) 
{
	render_frame(game);
	return (0);
}

int	start_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Erreur : Init mlx\n");
		return (0);
	}
	text_load(game, game->textures);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
	if (!game->win)
	{
		printf("Erreur : new_window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	game->img = mlx_new_image(game->mlx, WIDTH_IMG, HEIGHT_IMG);
	if (!game->img)
	{
		printf("Erreur : new_img\n");
		mlx_destroy_image(game->mlx, game->img);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	game->player = get_coord(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_loop(game->mlx);
	return(1);
}
