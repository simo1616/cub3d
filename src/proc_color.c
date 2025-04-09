/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:34 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 14:14:07 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_color_line(t_game *game, t_parser *parser)
{
	parser->match_color = 1;
	if (parser->clean_line[0] == 'F')
		parser->trimmed = ft_strtrim(parser->clean_line + 2, " \t\n");
	else if (parser->clean_line[0] == 'C')
		parser->trimmed = ft_strtrim(parser->clean_line + 2, " \t\n");
	if (!parser->trimmed)
	{
		//printf("\n\n***********FREE a  process_color_line via cleanup_all***********\n\n\n");
		ft_putstr_fd(ERR_MEM_ALLOC_COLOR, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	parse_color(game, parser->clean_line, parser->trimmed, parser);
	printf("Couleur lue: %s\n", parser->trimmed);
	//printf("\n\n***********FREE a  process_color_line via free(parser->trimmed);***********\n\n\n");
	free(parser->trimmed);
	parser->trimmed = NULL;
}
