/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:19 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/07 19:24:20 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ft_putstr_fd("Error\nDes données supp après la carte.\n", 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
	if (parser->empty_line_after_map)
	{
		ft_putstr_fd("Error\nDes caractères trouvés après des lignes vides suivant la carte.\n",
			2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
	if (!parser->match_text || !parser->match_color)
	{
		ft_putstr_fd("Error\nPosition de la map incorrecte (pas toutes les textures/couleurs lues).\n",
			2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
}
