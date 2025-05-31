/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:37 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:15:22 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Extrait le chemin de texture selon le préfixe NO/SO/WE/EA.
 *
 * - Si `clean_line` commence par "NO", 
 * `parser->trimmed = ft_strtrim(clean_line+3, " \t\n")`.
 * - Sinon si "SO", idem avec +3, etc.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 */
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

/**
 * @brief Vérifie que `parser->trimmed` n’est pas NULL après remise à zéro.
 *
 * - Si NULL, affiche `ERR_MEM_ALLOC_TEXTURE`, 
 * appelle `cleanup_all`, `exit(EXIT_FAILURE)`.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	check_trimmed_not_null(t_parser *parser)
{
	if (parser->trimmed == NULL)
	{
		ft_putstr_fd(ERR_MEM_ALLOC_TEXTURE, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Vérifie que `parser->trimmed` n’est pas vide après trimming.
 *
 * - Si `strlen(parser->trimmed) == 0`, 
 * affiche `ERR_EMPTY_TEXTURE_PATH`, nettoie tout et quitte.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	check_trimmed_not_empty(t_parser *parser)
{
	if (ft_strlen(parser->trimmed) == 0)
	{
		ft_putstr_fd(ERR_EMPTY_TEXTURE_PATH, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Traite une ligne de configuration de texture (NO/SO/WE/EA).
 *
 * - Met `parser->match_text = 1`.
 * - Appelle `trim_texture_path`, 
 * `check_trimmed_not_null`, `check_trimmed_not_empty`.
 * - Appelle `check_access(parser)`.
 * - Appelle `assign_texture(game, parser)`.
 * - Libère `parser->trimmed`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	process_texture_line(t_game *game, t_parser *parser)
{
	parser->match_text = 1;
	trim_texture_path(parser);
	check_trimmed_not_null(parser);
	check_trimmed_not_empty(parser);
	check_access(parser);
	assign_texture(game, parser);
	free(parser->trimmed);
}
