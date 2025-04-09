/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:59 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 15:08:07 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_and_pad_line(char *dest, char *src, int width)
{
	int	len;
	int	c;

	len = (int)ft_strlen(src);
	c = 0;
	while (c < len)
	{
		dest[c] = src[c];
		c++;
	}
	while (c < width)
	{
		dest[c] = ' ';
		c++;
	}
	dest[width] = '\0';
}

void	init_mapinfo_struct(t_mapinfo *info, char **map, int h, int w)
{
	int	r;

	info->height = h;
	info->width = w;
	info->map2d = malloc(sizeof(char *) * h);
	if (!info->map2d)
		error_and_exit(ERR_MAP_MALLOC);
	r = 0;
	while (r < h)
	{
		info->map2d[r] = malloc(sizeof(char) * (w + 1));
		if (!info->map2d[r])
			error_and_exit(ERR_MAP_MALLOC);
		copy_and_pad_line(info->map2d[r], map[r], w);
		r++;
	}
}

void	init_config_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->config.no_textures = NULL;
	game->config.so_textures = NULL;
	game->config.we_textures = NULL;
	game->config.ea_textures = NULL;
	game->config.color_sol[0] = -1;
	game->config.color_plafond[0] = -1;
	game->map = NULL;
}

void	init_parser(t_parser *parser, t_game *game)
{
	parser->match_text = 0;
	parser->match_color = 0;
	parser->map_started = false;
	parser->map_is_done = false;
	parser->empty_line_after_map = false;
	parser->line = NULL;
	parser->clean_line = NULL;
	parser->trimmed = NULL;
	parser->game = game;
	parser->state = malloc(sizeof(t_cleanup_state));
    if (parser->state)
    {
        parser->state->game_cleaned = false;
        parser->state->parser_cleaned = false;
    }
}
