/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:10:47 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 14:30:15 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx_ptr(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nInit mlx\n", 2);
		return (-1);
	}
	return (0);
}

static int	init_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		ft_putstr_fd("Error\nnew_window\n", 2);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	return (0);
}

static int	init_image(t_game *g)
{
	char	*addr;

	g->data_img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->data_img.img)
	{
		ft_putstr_fd("Error\nnew_image\n", 2);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		return (-1);
	}
	addr = mlx_get_data_addr(g->data_img.img,
			&g->data_img.bpp, &g->data_img.size_line, &g->data_img.endian);
	g->data_img.pixels = (int *)addr;
	g->data_img.size_line /= (g->data_img.bpp / 8);
	return (0);
}

int	start_mlx(t_game *game)
{
	if (init_mlx_ptr(game) || init_window(game) || init_image(game))
		return (-1);
	game->player = get_coord(game);
	text_load(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
	return (1);
}
