/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:35 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:57:23 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Affiche une erreur si la ligne `row` est vide et quitte (exit).
 *
 * - Affiche "Error\nLigne : <row> est vide.\n" 
 *   sur stderr via ft_putstr_fd/ft_putnbr_fd.
 * - Appelle `exit_text_with_error("", parser)`.
 *
 * @param row    Index de la ligne considérée.
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	print_line_error_empty(int row, t_parser *parser)
{
	ft_putstr_fd("Error\nLigne : ", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd(" est vide.\n", 2);
	exit_text_with_error("", parser);
}

/**
 * @brief Affiche une erreur si la ligne `row` 
 * ne se termine pas par '1' et quitte (exit).
 *
 * - Affiche "Error\nLigne : <row> ne finit pas par un mur '1'.\n".
 * - Appelle `exit_text_with_error("", parser)`.
 *
 * @param row    Index de la ligne considérée.
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	print_line_error_end(int row, t_parser *parser)
{
	ft_putstr_fd("Error\nLigne : ", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd(" ne finit pas par un mur '1'.\n", 2);
	exit_text_with_error("", parser);
}

/**
 * @brief Vérifie que `line` commence (après espaces) par le caractère '1'.
 *
 * - Avance un index i tant que `line[i]` est ' ' ou '\t'.
 * - Si `line[i] != '1'`, 
 *   appelle `exit_text_with_error(ERR_MAP_START_LINE, parser)`.
 *
 * @param line   Chaîne de la ligne de la map.
 * @param parser Pointeur vers `t_parser`.
 */
static void	check_line_starts_with_wall(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '1')
		exit_text_with_error(ERR_MAP_START_LINE, parser);
}

/**
 * @brief Vérifie que `line` se termine (avant espaces) par le caractère '1'.
 *
 * - Parcourt depuis la fin (strlen(line)-1) 
 * en décrémentant tant que c'est ' ' ou '\t'.
 * - Si l’indice devient < 0, appelle `print_line_error_empty(row, parser)`.
 * - Si `line[end] != '1'`, appelle `print_line_error_end(row, parser)`.
 *
 * @param line   Chaîne de la ligne de la map.
 * @param row    Numéro de ligne (pour le message d’erreur).
 * @param parser Pointeur vers `t_parser`.
 */
static void	check_line_ends_with_wall(char *line, int row, t_parser *parser)
{
	int	end;

	end = (int)strlen(line) - 1;
	while (end >= 0 && (line[end] == ' ' || line[end] == '\t'))
		end--;
	if (end < 0)
		print_line_error_empty(row, parser);
	if (line[end] != '1')
		print_line_error_end(row, parser);
}

/**
 * @brief Vérifie l’intégrité d’une ligne « middle » 
 * (ni première ni dernière) de la map.
 *
 * - Appelle `check_line_starts_with_wall` puis `check_line_ends_with_wall`.
 * - Utilisé pour les lignes intérieures à la carte (sans border).
 *
 * @param line   Chaîne de la ligne de la map.
 * @param row    Numéro de ligne (pour les messages d’erreur).
 * @param parser Pointeur vers `t_parser`.
 */
void	check_middle_line(char *line, int row, t_parser *parser)
{
	check_line_starts_with_wall(line, parser);
	check_line_ends_with_wall(line, row, parser);
}
