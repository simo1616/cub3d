/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:19 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:11:32 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Assigne une chaîne `trimmed` à `*texture_field` si non déjà définie.
 *
 * - Si `*texture_field != NULL`, affiche `error_msg`, libère `*texture_field`,
 *   appelle `cleanup_all` et `exit(EXIT_FAILURE)`.
 * - Sinon, `*texture_field = ft_strdup(trimmed)`. 
 * Si NULL, appelle `exit_text_with_error`.
 *
 * @param texture_field Pointeur vers le champ de texture (NO/SO/WE/EA).
 * @param trimmed       Chemin de texture déjà trimé.
 * @param error_msg     Message d’erreur si déjà défini ou si échec d’allocation.
 * @param parser        Pointeur vers la structure `t_parser`.
 */
void	assign_if_not_defined(char **texture_field, char *trimmed,
	char *error_msg, t_parser *parser)
{
	if (*texture_field != NULL)
	{
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

/**
 * @brief Traite une ligne de la map ou gère une ligne vide 
 * après que la map ait commencé.
 *
 * - Si `clean_line` est vide, appelle `handle_empty_line(parser)`.
 * - Sinon, appelle `check_map_errors(parser)`, met `parser->map_started = true`,
 *   puis `append_map_line(game, ft_strtrim(parser->line, "\n"))`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
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

/**
 * @brief Marque qu’une ligne vide a été rencontrée après que la map a commencé.
 *
 * - Si `parser->map_started == true`, alors `parser->map_is_done = true` et
 *   `parser->empty_line_after_map = true`.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	handle_empty_line(t_parser *parser)
{
	if (parser->map_started)
	{
		parser->map_is_done = true;
		parser->empty_line_after_map = true;
	}
}

/**
 * @brief Vérifie les erreurs de map en fonction de l’état de parsing.
 *
 * - Si `parser->map_is_done == true`, affiche `ERR_MAP_ADD` et quitte.
 * - Si `parser->empty_line_after_map == true`, affiche `ERR_MAP_BAD` et quitte.
 * - Si ni `match_text` ni `match_color` n’ont été rencontrés, 
 * affiche `ERR_MAP_POS` et quitte.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	check_map_errors(t_parser *parser)
{
	if (parser->map_is_done)
	{
		ft_putstr_fd(ERR_MAP_ADD, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	if (parser->empty_line_after_map)
	{
		ft_putstr_fd(ERR_MAP_BAD, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
	if (!parser->match_text || !parser->match_color)
	{
		ft_putstr_fd(ERR_MAP_POS, 2);
		cleanup_all(parser->game, parser);
		exit(EXIT_FAILURE);
	}
}
