/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:43:09 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/17 19:58:28 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


uint32_t tex_get(const t_tex *tex, int hor, int ver)
{
	int nbr;

	nbr = ver * tex->size_line + hor;
	return ((uint32_t)tex->pixels[nbr]);
}


void	text_load(t_game *g, t_tex tex[NBR])
{
	int		i;
	char	*paths[NBR];
	int		oct;

	paths[0] = g->config.no_textures;
	paths[1] = g->config.so_textures;
	paths[2] = g->config.we_textures;
	paths[3] = g->config.ea_textures;
	i = 0;
	oct = 0;
	while (i < NBR)
	{
		tex[i].img = mlx_xpm_file_to_image(g->mlx, paths[i], &tex[i].width,
				&tex[i].height);
		if (!tex[i].img)
			error_and_exit("Error\ncant load tex\n");
		tex[i].pixels = (int *)mlx_get_data_addr(tex[i].img, &tex[i].bpp,
				&tex[i].size_line, &tex[i].endian);	
		oct = tex[i].bpp / 8;
		tex[i].size_line /= oct; // convert sizeline en octet
		i++;
	}
}
