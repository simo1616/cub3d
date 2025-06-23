/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:10:47 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 21:04:10 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialise le contexte MLX (mlx_init) et vérifie la réussite.
 *
 * - Appelle `mlx_init()`.
 * - Si échec, affiche un message sur stderr et retourne -1.
 *
 * @param game Pointeur vers la structure de jeu (stockage du contexte MLX).
 * @return int 0 si succès, -1 en cas d’erreur.
 */
static int	init_mlx_ptr(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd(ERR_INIT_MLX, 2);
		return (-1);
	}
	return (0);
}

/**
 * @brief Crée la fenêtre MLX de taille WIDTH×HEIGHT.
 *
 * - Appelle `mlx_new_window` avec le contexte MLX, WIDTH,
	HEIGHT et le titre « Cub3D ».
 * - Si échec, affiche un message sur stderr, détruit l’affichage MLX,
	libère `game->mlx`,
 *   et retourne -1.
 *
 * @param game Pointeur vers la structure de jeu (contexte MLX).
 * @return int 0 si succès, -1 en cas d’erreur.
 */
static int	init_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		ft_putstr_fd(ERR_NEW_WINDOW, 2);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (-1);
	}
	return (0);
}

/**
 * @brief Crée l’image MLX et récupère son buffer pour accéder aux pixels.
 *
 * - Appelle `mlx_new_image` avec `game->mlx`, WIDTH et HEIGHT.
 * - Si échec, nettoie la fenêtre et l’affichage MLX, libère `game->mlx`,
	et retourne -1.
 * - Récupère le pointeur vers les pixels (`mlx_get_data_addr`) 
 	et calcule `size_line`.
 *
 * @param g Pointeur vers la structure de jeu (contexte MLX + data_img).
 * @return int 0 si succès, -1 en cas d’erreur.
 */
static int	init_image(t_game *g)
{
	char	*addr;

	g->data_img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->data_img.img)
	{
		ft_putstr_fd(ERR_NEW_IMAGE, 2);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		return (-1);
	}
	addr = mlx_get_data_addr(g->data_img.img, &g->data_img.bpp,
			&g->data_img.size_line, &g->data_img.endian);
	g->data_img.pixels = (int *)addr;
	g->data_img.size_line /= (g->data_img.bpp / 8);
	return (0);
}

/**
 * @brief Initialise MLX, crée la fenêtre, l’image,
	et lance la boucle graphique.
 *
 * - Appelle `init_mlx_ptr`, `init_window`, `init_image`.
 * - Place le joueur aux coordonnées initiales (`get_coord`).
 * - Charge les textures (`text_load`).
 * - Configure les hooks clavier (key_press, key_release).
 * - Configure le hook de fermeture de fenêtre (close_window).
 * - Configure la boucle principale (`mlx_loop_hook` puis `mlx_loop`).
 *
 * @param game Pointeur vers la structure de jeu.
 * @return int 1 si tout s’est bien passé, 0 ou
	-1 en cas d’erreur d’initialisation.
 */
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
