/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:37 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 08:19:45 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_texture_path(t_parser *parser)
{
	if (parser->clean_line[0] == 'N' && parser->clean_line[1] == 'O')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
	else if (parser->clean_line[0] == 'S' && parser->clean_line[1] == 'O')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
	else if (parser->clean_line[0] == 'W' && parser->clean_line[1] == 'E')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
	else if (parser->clean_line[0] == 'E' && parser->clean_line[1] == 'A')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
}

static void	check_trimmed_not_null(t_parser *parser)
{
	if (parser->trimmed == NULL)
	{
		//printf("\n\n***********FREE a  check_trimmed_not_null via cleanup_all***********\n\n\n");

		ft_putstr_fd(ERR_MEM_ALLOC_TEXTURE, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
}

static void	check_trimmed_not_empty(t_parser *parser)
{
	if (ft_strlen(parser->trimmed) == 0)
	{
		//printf("\n\n***********FREE a  check_trimmed_not_empty via cleanup_all***********\n\n\n");

		ft_putstr_fd(ERR_EMPTY_TEXTURE_PATH, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
}

void	process_texture_line(t_game *game, t_parser *parser)
{
	parser->match_text = 1;
	trim_texture_path(parser);
	check_trimmed_not_null(parser);
	check_trimmed_not_empty(parser);
	check_access(parser);
	assign_texture(game, parser);
	//printf("\n\n***********FREE (%s) =>  process_texture_line via free(parser->trimmed);***********\n\n\n", parser->trimmed);

	free(parser->trimmed);
}
