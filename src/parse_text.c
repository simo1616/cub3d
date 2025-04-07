/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:26 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/07 19:24:28 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_with_error(char *msg, t_parser *parser)
{
	ft_putstr_fd(msg, 2);
	free(parser->trimmed);
	free(parser->clean_line);
	free(parser->line);
	exit(EXIT_FAILURE);
}

static void	assign_if_not_defined(char **texture_field, char *trimmed,
		char *error_msg, t_parser *parser)
{
	if (*texture_field != NULL)
	{
		ft_putstr_fd(error_msg, 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
	*texture_field = ft_strdup(trimmed);
	if (*texture_field == NULL)
		exit_with_error(error_msg, parser);
}

static void	assign_no(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.no_textures, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_NO, parser);
}

static void	assign_so(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.so_textures, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_SO, parser);
}

static void	assign_we(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.we_textures, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_WE, parser);
}

static void	assign_ea(t_game *game, t_parser *parser)
{
	assign_if_not_defined(&game->config.ea_textures, parser->trimmed,
		ERR_TEXTURE_ALREADY_DEFINED_EA, parser);
}

void	assign_texture(t_game *game, t_parser *parser)
{
	if (!ft_strncmp(parser->clean_line, "NO ", 3))
		assign_no(game, parser);
	else if (!ft_strncmp(parser->clean_line, "SO ", 3))
		assign_so(game, parser);
	else if (!ft_strncmp(parser->clean_line, "WE ", 3))
		assign_we(game, parser);
	else if (!ft_strncmp(parser->clean_line, "EA ", 3))
		assign_ea(game, parser);
}
