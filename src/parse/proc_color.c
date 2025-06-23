/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:34 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 15:27:22 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Traite une ligne de configuration de couleur (F ou C).
 *
 * - Met `parser->match_color = 1`.
 * - Si `clean_line[0] == 'F'`, `
 * parser->trimmed = ft_strtrim(clean_line + 2, " \t\n")`.
 *   Sinon si `'C'`, fait de même avec `clean_line + 2`.
 * - Si `parser->trimmed == NULL`, affiche `ERR_MEM_ALLOC_COLOR`, 
 * publie `exit(EXIT_FAILURE)`.
 * - Appelle `parse_color(game, parser->clean_line, parser->trimmed, parser)`.
 * - Libère `parser->trimmed`.
 *
 * @param game   Pointeur vers `t_game`.
 * @param parser Pointeur vers `t_parser`.
 */
void	process_color_line(t_game *game, t_parser *parser)
{
	if (parser->config_complete)//
    	error_and_exit(parser, "Error\nHeader après le début de la map.\n");//

	parser->match_color = 1;
	if (parser->clean_line[0] == 'F')
		parser->trimmed = ft_strtrim(parser->clean_line + 2, " \t\n");
	else if (parser->clean_line[0] == 'C')
		parser->trimmed = ft_strtrim(parser->clean_line + 2, " \t\n");
	if (!parser->trimmed)
	{
		ft_putstr_fd(ERR_MEM_ALLOC_COLOR, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	parse_color(game, parser->clean_line, parser->trimmed, parser);
	free(parser->trimmed);
	parser->trimmed = NULL;
}
