/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:25:32 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/28 12:17:02 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gère le cas où le fichier est vide (première ligne NULL).
 *
 * @param parser Pointeur vers la structure `t_parser`.
 * @param fd     Descripteur de fichier à fermer.
 */
void	handle_empty_file(t_parser *parser, int fd)
{
	ft_putstr_fd(ERR_MAP_EMPTY, 2);
	close(fd);
	cleanup_get_next_line();
	if (parser->state)
	{
		free(parser->state);
		parser->state = NULL;
	}
	exit(EXIT_FAILURE);
}

/**
 * @brief Traite une ligne lue et libère les ressources associées.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	process_and_cleanup_line(t_game *game, t_parser *parser)
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
}

/**
 * @brief Boucle principale du parsing : lit ligne par ligne via `get_next_line`.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 * @param fd     Descripteur de fichier de la map.
 */
void	parse_loop(t_game *game, t_parser *parser, int fd)
{
	parser->line = get_next_line(fd);
	if (!parser->line)
		handle_empty_file(parser, fd);
	while (parser->line)
	{
		process_and_cleanup_line(game, parser);
		parser->line = get_next_line(fd);
	}
	cleanup_get_next_line();
}

/**
 * @brief Vérifie la validité finale après le parsing.
 *
 * @param game   Pointeur vers la structure (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 * @return int 0 si parsing OK, 1 sinon.
 */
int	check_parsing(t_game *game, t_parser *parser)
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
 * @brief Ouvre le fichier `.cub` et vérifie l'extension ".cub".
 *
 * @param file_name Nom du fichier .cub.
 * @param parser    Pointeur vers la structure `t_parser`.
 * @return int Descripteur de fichier (>= 0) ou -1 en cas d'erreur.
 */
int	open_and_validate(char *file_name)
{
	int	fd;

	fd = open_map_file(file_name);
	if (fd == -1)
	{
		cleanup_get_next_line();
		return (-1);
	}
	return (fd);
}
