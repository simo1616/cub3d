/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:37:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:28:01 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialise chaque texture à NULL/0 dans le tableau de textures.
 *
 * - Parcourt `text[0]` à `text[NBR_TEX-1]` et met tous les champs à NULL ou 0.
 *
 * @param text Tableau de `t_tex` de taille NBR_TEX.
 */
static void	init_textures(t_tex text[NBR_TEX])
{
	int	i;

	i = 0;
	while (i < NBR_TEX)
	{
		text[i].img = NULL;
		text[i].pixels = NULL;
		text[i].width = 0;
		text[i].height = 0;
		text[i].bpp = 0;
		text[i].size_line = 0;
		text[i].endian = 0;
		i++;
	}
}

/**
 * @brief Réinitialise la structure `t_data_img` à des valeurs vides.
 *
 * - Met `img`, `pixels` à NULL ; `bpp`, `size_line`, `endian` à 0.
 *
 * @param data_img Pointeur vers la structure `t_data_img` à initialiser.
 */
static void	init_data_img(t_data_img *data_img)
{
	data_img->img = NULL;
	data_img->pixels = NULL;
	data_img->bpp = 0;
	data_img->size_line = 0;
	data_img->endian = 0;
}

/**
 * @brief Initialise les chemins de textures et les couleurs à
	-1 pour th Floor/ceiling.
 *
 * - Met tous les pointeurs de texture (`no_texture`, `so_texture`,
	`we_texture`, `ea_texture`) à NULL.
 * - Initialise `floor_color` et `ceiling_color` à -1 (trois composantes).
 *
 * @param config Pointeur vers la structure `t_config`.
 */
static void	init_config(t_config *config)
{
	int	i;

	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	i = 0;
	while (i < 3)
	{
		config->floor_color[i] = -1;
		config->ceiling_color[i] = -1;
		i++;
	}
}

/**
 * @brief Initialise la position de départ et les flags de touches du joueur.
 *
 * - Place le joueur au centre de l’écran (`WIDTH/2`, `HEIGHT/2`),
	angle `-PI/2`.
 * - Met toutes les touches (`key_up`, `key_down`, `key_left`, ...) à false.
 *
 * @param player Pointeur vers la structure `t_player`.
 */
static void	init_player_defaults(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = -PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

/**
 * @brief Initialise tous les champs de `t_game` avant le parsing.
 *
 * - Réinitialise la totalité de la structure `game` à 0 (`ft_memset`).
 * - Appelle `init_data_img`, `init_config`, met `game->map = NULL`.
 * - Appelle `init_player_defaults` et `init_textures`.
 *
 * @param game Pointeur vers la structure de jeu à initialiser.
 */
void	init_structs(t_game *game)
{
	ft_memset(game, 0, sizeof(*game));
	init_data_img(&game->data_img);
	init_config(&game->config);
	game->map = NULL;
	init_player_defaults(&game->player);
	init_textures(game->textures);
}
