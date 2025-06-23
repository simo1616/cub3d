/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:52 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 21:19:29 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Affiche un message d’erreur, nettoie le jeu, puis quitte.
 *
 * - Affiche `msg` sur stderr (`ft_putstr_fd`).
 * - Appelle `cleanup_before_exit(game)` pour libérer ressources jeu.
 * - `exit(EXIT_FAILURE)`.
 *
 * @param game Pointeur vers la structure de jeu (`t_game`).
 * @param msg  Message d’erreur à afficher.
 */
void	error_exit_game(t_game *game, char *msg)
{
	ft_putstr_fd(msg, 2);
	cleanup_before_exit(game);
	exit(EXIT_FAILURE);
}

/**
 * @brief Affiche un message d’erreur lié au parsing, 
 * nettoie parser + jeu, puis quitte.
 *
 * - Affiche `msg` sur stderr (`ft_putstr_fd`).
 * - Appelle `cleanup_all(parser->game, parser)` 
 *   pour libérer map, textures, etc.
 * - Libère `parser->state`.
 * - `exit(EXIT_FAILURE)`.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 * @param msg    Message d’erreur à afficher.
 */
void	exit_text_with_error(char *msg, t_parser *parser)
{
	ft_putstr_fd(msg, 2);
	cleanup_all(parser->game, parser);
	free(parser->state);
	exit(EXIT_FAILURE);
}

/**
 * @brief Affiche un message d’erreur, 
 * nettoie le parsing en cours, puis quitte.
 *
 * - Affiche `msg` sur stderr (`ft_putstr_fd`).
 * - Appelle `cleanup_get_next_line()` pour vider le buffer.
 * - Appelle `cleanup_all(parser->game, parser)` 
 *   pour libérer map, textures, etc.
 * - Libère `parser->state`.
 * - `exit(EXIT_FAILURE)`.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 * @param msg    Message d’erreur à afficher.
 */
void	error_and_exit(t_parser *parser, char *msg)
{
	ft_putstr_fd(msg, 2);
	cleanup_get_next_line();
	cleanup_all(parser->game, parser);
	free(parser->state);
	exit(EXIT_FAILURE);
}

/**
 * @brief Même que `error_and_exit`, mais libère d’abord un tableau `tokens`.
 *
 * - Libère chaque `tokens[i]` puis `tokens`.
 * - Affiche `msg` sur stderr, 
 * 	 appelle `cleanup_get_next_line()`, `cleanup_all(...)`.
 * - Libère `parser->state`.
 * - `exit(EXIT_FAILURE)`.
 *
 * @param parser Pointeur vers la structure `t_parser`.
 * @param tokens Tableau de chaînes à libérer avant l’erreur.
 * @param msg    Message d’erreur à afficher.
 */
void	error_and_exit_free(t_parser *parser, char **tokens, char *msg)
{
	free_split(tokens);
	ft_putstr_fd(msg, 2);
	cleanup_get_next_line();
	cleanup_all(parser->game, parser);
	free(parser->state);
	exit(EXIT_FAILURE);
}

/**
 * @brief Vérifie qu’une valeur de couleur est dans [0,255], sinon quitte.
 *
 * - Si `value < 0` ou `value > 255` : affiche “Error: 
 * Couleur invalide: <value>” et `exit_text_with_error`.
 *
 * @param value  Entier représentant une composante R/G/B.
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	check_color_value(int value, t_parser *parser)
{
	if (value < 0 || value > 255)
	{
		ft_putstr_fd(ERR_COULEUR_INVALIDE, 2);
		ft_putnbr_fd(value, 2);
		ft_putchar_fd('\n', 2);
		exit_text_with_error("", parser);
	}
}
