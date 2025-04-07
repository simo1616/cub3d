/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:30 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/07 19:24:31 by mbendidi         ###   ########.fr       */
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

int	ft_parse(t_game *game, char *file_name)
{
	t_parser	parser;
	int			fd;

	init_parser(&parser);
	game->map = NULL;
	fd = open_map_file(file_name);
	if (fd == -1)
		return (1);
	while ((parser.line = get_next_line(fd)) != NULL)
	{
		parser.clean_line = ft_strtrim(parser.line, " \t\n");
		process_line(game, &parser);
		if (parser.clean_line)
		{
			free(parser.clean_line);
			parser.clean_line = NULL;
		}
		free(parser.line);
		parser.line = NULL;
	}
	check_validate_map(game);
	final_check_config(game);
	close(fd);
	return (0);
}
