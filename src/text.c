/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:59:24 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/04 19:31:22 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void fill_paths(char *paths[NBR_TEX], t_config *cfg)
{
	paths[0] = cfg->no_texture;
	paths[1] = cfg->so_texture;
	paths[2] = cfg->we_texture;
	paths[3] = cfg->ea_texture;
}

void text_load(t_game *game)
{	
	int i;
    char *paths[NBR_TEX];

	i = 0;
	fill_paths(paths, &game->config);
	while (i < NBR_TEX)
	{
		if (!paths[i] || paths[i][0] == '\0')
			error_and_exit("Error\nMissing texture path\n");
		if (ft_strlen(paths[i]) < 4
		 || ft_strcmp(paths[i] + ft_strlen(paths[i]) - 4, ".xpm") != 0)
			error_and_exit("Error\nTexture file must end with .xpm\n");
		game->textures[i].img = mlx_xpm_file_to_image(
			game->mlx,
			paths[i],
			&game->textures[i].width,
			&game->textures[i].height
		);
		if (!game->textures[i].img)
			error_and_exit("Error\nCannot load texture\n");
		char *addr = mlx_get_data_addr(
			game->textures[i].img,
			&game->textures[i].bpp,
			&game->textures[i].size_line,
			&game->textures[i].endian
		);
		game->textures[i].pixels = (int *)addr;
		game->textures[i].size_line /= (game->textures[i].bpp / 8);
		i++;
	}
}
