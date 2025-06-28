/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:11:31 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/27 22:12:29 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Traite une ligne lue : texture, couleur ou map.
 *
 * - Si `parser->clean_line == NULL` ou vide,
 * appelle `handle_empty_line(parser)`.
 * - Sinon, si `clean_line` commence par "NO "/"SO "/"WE "/"EA ",
 * appelle `process_texture_line`.
 * - Sinon, si commence par "F "/"C ", appelle `process_color_line`.
 * - Sinon, appelle `process_map_line`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */

#include "cub3d.h"

void	process_line(t_game *game, t_parser *parser)
{
	if (!parser->clean_line || ft_strlen(parser->clean_line) == 0)
	{
		handle_empty_line(parser);
		return ;
	}
	if (is_texture_attempt(parser->clean_line))
	{
		if (is_valid_texture_format(parser->clean_line))
			process_texture_line(game, parser);
		else
			error_and_exit(parser, ERR_NFORMAT_TEXTURE);
	}
	else if (is_color_attempt(parser->clean_line))
	{
		if (is_valid_color_format(parser->clean_line))
			process_color_line(game, parser);
		else
			error_and_exit(parser, ERR_NFORMAT_COULEUR);
	}
	else if (parser->map_started || is_map_line(parser->clean_line))
		process_map_line(game, parser);
	else
		error_and_exit(parser, ERR_LINE_INVALID);
}
