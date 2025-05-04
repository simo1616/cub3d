/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:56 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/04 19:32:06 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_parser_resources(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->line)
	{
		free(parser->line);
		parser->line = NULL;
	}
	if (parser->clean_line)
	{
		free(parser->clean_line);
		parser->clean_line = NULL;
	}
	if (parser->trimmed != NULL)
	{
		free(parser->trimmed);
		parser->trimmed = NULL;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->no_texture)
		free(config->no_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->ea_texture)
	{
		free(config->ea_texture);
	}
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
}

void	cleanup_all(t_game *game, t_parser *parser)
{
	if (game && parser && parser->state && !parser->state->game_cleaned)
	{
		parser->state->game_cleaned = true;
		free_config(&game->config);
		if (game->map)
		{
			free_map(game->map);
			game->map = NULL;
		}
	}
	if (parser && parser->state && !parser->state->parser_cleaned)
	{
		parser->state->parser_cleaned = true;
		parser->trimmed = NULL;
		cleanup_parser_resources(parser);
	}
	if (parser && parser->state)
	{
		free(parser->state);
		parser->state = NULL;
	}
}

void	cleanup_before_exit(t_game *game)
{
	free_config(&game->config);
	free_map(game->map);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
	}
}
