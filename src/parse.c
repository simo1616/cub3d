/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:30 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/08 20:22:36 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(ERR_OPEN_FILE, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

void	process_line(t_game *game, t_parser *parser)
{
	if (!parser->clean_line || ft_strlen(parser->clean_line) == 0)
	{
		handle_empty_line(parser);
		return ;
	}
	if (ft_strlen(parser->clean_line) > 0 && (!ft_strncmp(parser->clean_line,
				"NO ", 3) || !ft_strncmp(parser->clean_line, "SO ", 3)
			|| !ft_strncmp(parser->clean_line, "WE ", 3)
			|| !ft_strncmp(parser->clean_line, "EA ", 3)))
	{
		process_texture_line(game, parser);
	}
	else if (ft_strlen(parser->clean_line) > 0
		&& (!ft_strncmp(parser->clean_line, "F ", 2)
			|| !ft_strncmp(parser->clean_line, "C ", 2)))
	{
		process_color_line(game, parser);
	}
	else
		process_map_line(game, parser);
}

static void	parse_loop(t_game *game, t_parser *parser, int fd)
{
	parser->line = get_next_line(fd);
	if (!parser->line)
	{
		ft_putstr_fd(ERR_MAP_EMPTY, 2);
		close(fd);
		cleanup_get_next_line();
		exit(EXIT_FAILURE);
	}
	while (parser->line)
	{
		parser->clean_line = ft_strtrim(parser->line, " \t\n");
		process_line(game, parser);
		if (parser->clean_line)
		{
			free(parser->clean_line);
			parser->clean_line = NULL;
		}
		free(parser->line);
		parser->line = NULL;
		parser->line = get_next_line(fd);
	}
	cleanup_get_next_line();
}

int	ft_parse(t_game *game, char *file_name)
{
	t_parser	parser;
	int			fd;
	int 		result;

	init_parser(&parser, game);
	game->map = NULL;
	fd = open_map_file(file_name);
	if (fd == -1)
	{
		cleanup_get_next_line();
		return (EXIT_FAILURE);
	}
	parse_loop(game, &parser, fd);
	
	result = 0;
	if (game->map)
	{
		check_validate_map(game, &parser);
		final_check_config(game);
	}
	else
	{
		ft_putstr_fd(ERR_MAP_NOT_DEFINED, 2);
		result = 1;
	}
	close(fd);
	cleanup_get_next_line();
	return (result);
}
