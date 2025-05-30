/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:10:47 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/30 17:35:44 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_mlx(t_game *game)
{
	char	*addr;
	
	game->mlx = mlx_init();
	printf("[start_mlx] mlx_init ok: %p\n", game->mlx);
	if (!game->mlx)
	{
		printf("Erreur : Init mlx\n");
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	printf("[start_mlx] new_window ok: %p\n", game->win);
	if (!game->win)
	{
		printf("Erreur : new_window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	game->data_img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	printf("[start_mlx] new_image ok: %p\n", game->data_img.img);
	if (!game->data_img.img)
	{
		printf("Erreur : new_img\n");
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	addr = mlx_get_data_addr(game->data_img.img, &game->data_img.bpp, &game->data_img.size_line,&game->data_img.endian);
	game->data_img.pixels = (int *)addr;
	game->data_img.size_line /= (game->data_img.bpp / 8);
	game->player = get_coord(game);
	text_load(game);
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);

	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
	return(1);
}
