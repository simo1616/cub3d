/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:59:24 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 20:46:27 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Remplit le tableau `paths[]` avec les chemins de texture 
 * issus de la configuration.
 *
 * - `paths[0] = cfg->no_texture`  
 * - `paths[1] = cfg->so_texture`  
 * - `paths[2] = cfg->we_texture`  
 * - `paths[3] = cfg->ea_texture`  
 *
 * Cette fonction est appelée au début de `text_load` pour préparer la
 * liste des quatre chemins XPM à charger.
 *
 * @param paths Tableau de taille NBR_TEX (4) qui recevra 
 * les pointeurs vers les chaînes de chemins.
 * @param cfg   Pointeur vers la structure `t_config` 
 * contenant les quatre chemins (no/so/we/ea).
 */
static void	fill_paths(char *paths[NBR_TEX], t_config *cfg)
{
	paths[0] = cfg->no_texture;
	paths[1] = cfg->so_texture;
	paths[2] = cfg->we_texture;
	paths[3] = cfg->ea_texture;
}

/**
 * @brief Charge toutes les textures XPM définies dans `game->config`.
 *
 * - Récupère les chemins depuis `game->config.
 * {no,so,we,ea}_texture` dans `paths[]`.
 * - Pour chaque i ∈ [0..NBR_TEX-1] :
 *   - Vérifie `paths[i]` non-NULL et se terminant par “.xpm”.
 *   - Appelle `mlx_xpm_file_to_image` pour charger l’image.
 *   - Si échec, appelle `error_exit_game`.
 *   - Récupère `pixels`, `bpp`, `size_line`, `endian` via `mlx_get_data_addr`.
 * - Incrémente i jusqu’à NBR_TEX.
 *
 * @param game Pointeur vers la structure de jeu (`t_game`).
 */
void	text_load(t_game *game)
{
	int		i;
	char	*paths[NBR_TEX];
	char	*addr;

	i = 0;
	fill_paths(paths, &game->config);
	while (i < NBR_TEX)
	{
		if (!paths[i] || paths[i][0] == '\0')
			error_exit_game(game, ERR_NMISSING_TEXTURE_PATH);
		if (ft_strlen(paths[i]) < 4 || ft_strcmp(paths[i] + ft_strlen(paths[i])
				- 4, ".xpm") != 0)
			error_exit_game(game, ERR_NTEXTURE_FILE_MUST);
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, paths[i],
				&game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
			error_exit_game(game, ERR_NCANNOT_LOAD_TEXTURE);
		addr = mlx_get_data_addr(game->textures[i].img, &game->textures[i].bpp,
				&game->textures[i].size_line, &game->textures[i].endian);
		game->textures[i].pixels = (int *)addr;
		game->textures[i].size_line /= (game->textures[i].bpp / 8);
		i++;
	}
}
