/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:59:24 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/03 12:05:02 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void text_load(t_game *game)
{
    char *paths[NBR_TEX] = {
        game->config.no_texture,
        game->config.so_texture,
        game->config.we_texture,
        game->config.ea_texture
    };

    for (int i = 0; i < NBR_TEX; i++)
    {
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
    }
}
