/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:30 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/28 12:16:19 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gère l'erreur d'ouverture de fichier et nettoie les ressources.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 * @return int EXIT_FAILURE.
 */
static int	handle_file_open_error(t_parser *parser)
{
	cleanup_get_next_line();
	if (parser->state)
	{
		free(parser->state);
		parser->state = NULL;
	}
	return (EXIT_FAILURE);
}

/**
 * @brief Finalise le parsing et nettoie les ressources.
 *
 * @param game   Pointeur vers la structure de jeu (`t_game`).
 * @param parser Pointeur vers la structure `t_parser`.
 * @param result Résultat du parsing.
 * @return int Résultat final du parsing.
 */
static int	finalize_parsing(t_game *game, t_parser *parser, int result)
{
	cleanup_get_next_line();
	if (parser->state)
	{
		free(parser->state);
		parser->state = NULL;
	}
	if (result != EXIT_SUCCESS)
	{
		cleanup_all(game, parser);
		return (result);
	}
	return (result);
}

/**
 * @brief Fonction principale de parsing du programme.
 *
 * @param game      Pointeur vers la structure de jeu (`t_game`).
 * @param file_name Chaîne avec le nom du fichier .cub.
 * @return int EXIT_SUCCESS si OK, sinon code d'erreur.
 */
int	ft_parse(t_game *game, char *file_name)
{
	t_parser	parser;
	int			fd;
	int			result;

	init_parser(&parser, game);
	game->map = NULL;
	fd = open_and_validate(file_name);
	if (fd == -1)
		return (handle_file_open_error(&parser));
	parse_loop(game, &parser, fd);
	result = check_parsing(game, &parser);
	close(fd);
	return (finalize_parsing(game, &parser, result));
}
