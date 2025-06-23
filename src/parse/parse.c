/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:30 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 19:10:26 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			error_and_exit(parser, "Error\nFormat de texture invalide.\n");
	}
	else if (is_color_attempt(parser->clean_line))
	{
		if (is_valid_color_format(parser->clean_line))
			process_color_line(game, parser);
		else
			error_and_exit(parser, "Error\nFormat de couleur invalide.\n");
	}
	else if (parser->map_started || is_map_line(parser->clean_line))
		process_map_line(game, parser);
	else
		error_and_exit(parser,
			"Error\nLigne non reconnue dans la configuration.\n");
}

/**

 * @brief Boucle principale du parsing : lit ligne par ligne 
 	via `get_next_line`.
 *
 * - Lit la première ligne (`parser->line = get_next_line(fd)`).
 * - Tant que `parser->line != NULL` :
 *   - `parser->clean_line = ft_strtrim(parser->line, " \t\n")`.
 *   - Appelle `process_line(game, parser)`.
 *   - Libère `parser->clean_line` et `parser->line`.
 *   - Lit la ligne suivante.
 * - À la fin, appelle `cleanup_get_next_line()`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 * @param fd     Descripteur de fichier de la map.
 */
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

/**
 * @brief Vérifie la validité finale après le parsing.
 *
 * - Si `game->map != NULL` :
 *   - Appelle `check_validate_map` (vérification de fermeture).
 *   - Appelle `final_check_config` (textures/couleurs/map).
 *   - Retourne 0.
 * - Sinon, affiche `ERR_MAP_NOT_DEFINED` et retourne 1.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 * @return int 0 si parsing OK, 1 sinon.
 */
static int	check_parsing(t_game *game, t_parser *parser)
{
	if (game->map)
	{
		check_validate_map(game, parser);
		final_check_config(game, parser);
		return (0);
	}
	else
	{
		ft_putstr_fd(ERR_MAP_NOT_DEFINED, 2);
		return (1);
	}
}

/**
 * @brief Ouvre le fichier `.cub` et vérifie l’extension “.cub”.
 *
 * - Appelle `open_map_file(file_name)`. Si retourné -1,
 *   appelle `cleanup_get_next_line()` et `free(parser->state)` puis retourne
	-1.
 * - Sinon, retourne le fd valide.
 *
 * @param file_name Nom du fichier .cub.
 * @param parser    Pointeur vers la structure `t_parser`.
 * @return int Descripteur de fichier (>= 0) ou -1 en cas d’erreur.
 */
static int	open_and_validate(char *file_name, t_parser *parser)
{
	int	fd;

	fd = open_map_file(file_name);
	if (fd == -1)
	{
		cleanup_get_next_line();
		free(parser->state);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Fonction principale de parsing du programme.
 *
 * - Initialise `parser` via `init_parser`.
 * - Définit `game->map = NULL`.
 * - `fd = open_and_validate(file_name, &parser)`. Si -1, retourne EXIT_FAILURE.
 * - Appelle `parse_loop(game, &parser, fd)`.
 * - `result = check_parsing(game, &parser)`. Ferme FD.
 * - Si `result != EXIT_SUCCESS` :
 *   - Appelle `cleanup_get_next_line()`,
 * `cleanup_all(game, &parser)`,
 * `free(parser.state)`,
 *  retourne `result`.
 * - Sinon, `cleanup_get_next_line()`, `free(parser.state)`, retourne `result`.
 *
 * @param game      Pointeur vers la structure de jeu (`t_game`).
 * @param file_name Chaîne avec le nom du fichier .cub.
 * @return int EXIT_SUCCESS si OK, sinon code d’erreur.
 */
int	ft_parse(t_game *game, char *file_name)
{
	t_parser	parser;
	int			fd;
	int			result;

	init_parser(&parser, game);
	game->map = NULL;
	fd = open_and_validate(file_name, &parser);
	if (fd == -1)
		return (EXIT_FAILURE);
	parse_loop(game, &parser, fd);
	result = check_parsing(game, &parser);
	close(fd);
	if (result != EXIT_SUCCESS)
	{
		cleanup_get_next_line();
		cleanup_all(game, &parser);
		free(parser.state);
		return (result);
	}
	cleanup_get_next_line();
	free(parser.state);
	return (result);
}
