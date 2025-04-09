/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:19 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 08:34:21 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_if_not_defined(char **texture_field, char *trimmed,
	char *error_msg, t_parser *parser)
{
	if (*texture_field != NULL)
	{
		//printf("\n\n***********FREE a  assign_if_not_defined via cleanup_all***********\n\n\n");
		ft_putstr_fd(error_msg, 2);
		free(*texture_field);
		*texture_field = NULL;
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	*texture_field = ft_strdup(trimmed);
	if (*texture_field == NULL)
		exit_text_with_error(error_msg, parser);
}

void	process_map_line(t_game *game, t_parser *parser)
{
	if (ft_strlen(parser->clean_line) == 0)
	{
		handle_empty_line(parser);
		return ;
	}
	check_map_errors(parser);
	parser->map_started = true;
	append_map_line(game, ft_strtrim(parser->line, "\n"));
}

void	handle_empty_line(t_parser *parser)
{
	if (parser->map_started)
	{
		parser->map_is_done = true;
		parser->empty_line_after_map = true;
	}
}

void	check_map_errors(t_parser *parser)
{
	if (parser->map_is_done)
	{
		//printf("\n\n***********FREE a  check_map_errors 1 if via cleanup_all***********\n\n\n");
		ft_putstr_fd(ERR_MAP_ADD, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	if (parser->empty_line_after_map)
	{
		//printf("\n\n***********FREE a  check_map_errors 2 if via cleanup_all***********\n\n\n");
		ft_putstr_fd(ERR_MAP_BAD, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	if (!parser->match_text || !parser->match_color)
	{
		//printf("\n\n***********FREE (%s) =>  check_map_errors 3 if via cleanup_all***********\n\n\n", parser->trimmed);

		ft_putstr_fd(ERR_MAP_POS, 2);
		cleanup_all(parser->game, parser);
		//parser->trimmed = NULL;
		exit(EXIT_FAILURE);
	}
}
