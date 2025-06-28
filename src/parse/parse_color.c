/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:12 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/27 21:11:11 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Vérifie que la chaîne de valeurs RGB contient exactement deux virgules
 * et qu’elle ne se termine pas par une virgule.
 *
 * - Parcourt toute la chaîne `s`, compte les occurrences de ','.
 * - Si le nombre de virgules n’est pas égal à 2, ou si le dernier
 *   caractère de la chaîne est ',', quitte avec ERR_INVALID_COLOR_FORMAT.
 *
 * @param s Chaîne de caractères contenant les trois valeurs séparées
 * par des virgules.
 * @param p Pointeur vers le parser, utilisé pour remonter l’erreur.
 */
bool	check_commas(char *s)
{
	char	*end;
	int		commas;

	if (!s)
		return (false);
	commas = 0;
	end = s + ft_strlen(s) - 1;
	while (*s)
		if (*s++ == ',')
			commas++;
	if (commas != 2 || *end == ',')
		return (false);
	return (true);
}

/**
 * @brief Scinde la chaîne `str` par « , »,
 * vérifie qu’il y a exactement 3 tokens.
 *
 * - Appelle `ft_split(str, ',')`.
 * - Si `tokens == NULL`, appelle `error_and_exit(parser, ERR_MEM_ALLOC_COLOR)`.
 * - Compte le nombre de tokens : si ≠ 3, libère tokens et
 *  `error_and_exit_free(parser, tokens, ERR_INVALID_COLOR_FORMAT)`.
 * - Vérifie : pour i ∈ [0..2], si `tokens[i] == NULL`,
 *   libère et `error_and_exit_free(parser,
 *   tokens, "Format de couleur invalide\n")`.
 * - Renvoie le tableau `tokens` (à libérer ensuite).
 *
 * @param str    Chaîne « r,g,b » à scinder.
 * @return char** Tableau de 3 chaînes (tokens),
 * ou ne retourne pas en cas d’erreur.
 */
char	**split_and_validate_color(char *str)
{
	char	**tokens;

	if (!str)
		return (NULL);
	tokens = ft_split(str, ',');
	if (!tokens)
		return (NULL);
	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		free_split(tokens);
		return (NULL);
	}
	return (tokens);
}

/**
 * Assigne et valide trois composantes RGB depuis des tokens.
 *
 * Si target[0] != -1, libère tokens et quitte avec
 * "Error\nCouleur déjà définie.\n".
 * Pour chaque token i ∈ [0..2] :
 *   - Trim espaces/tabs autour via ft_strtrim.
 *   - Si la chaîne nettoyée est vide ou non entière, libère clean
 *     et tokens puis quitte avec "Error\nFormat de couleur invalide\n".
 *   - Convertit en int via ft_atoi, puis libère clean.
 *   - Vérifie que la valeur ∈ [0,255] via check_color_value.
 *
 * @param target  Tableau de 3 entiers (floor_color ou ceiling_color).
 * @param tokens  Tableau de 3 chaînes contenant r,g,b.
 * @param parser  Pointeur vers le parser pour gérer les erreurs.
 */
bool	assign_color(int target[3], char **tokens, t_parser *parser)
{
	char	*clean;
	int		i;

	if (!target || !tokens || !parser)
		return (false);
	if (target[0] != -1)
		return (false);
	i = 0;
	while (i < 3)
	{
		clean = ft_strtrim(tokens[i], " \t");
		if (!clean || !*clean || !is_integer(clean))
		{
			free(clean);
			return (false);
		}
		target[i] = ft_atoi(clean);
		free(clean);
		if (target[i] < 0 || target[i] > 255)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Parse une ligne de couleur (clean_line commence par "F " ou "C ").
 *
 * - Scinde `color_str` (chaine après « F » ou « C »)
 * 		via `split_and_validate_color`.
 * - Si `clean_line` commence par "F ",
 * 		appelle `assign_color(game->config.floor_color,…)`.
 *   Sinon si "C ", appelle `assign_color(game->config.ceiling_color,…)`.
 *   Sinon, libère tokens et
 * 	`error_and_exit(parser, ERR_UNKNOWN_COLOR_IDENTIFIER)`.
 * - Libère tokens à la fin.
 *
 * @param game       Pointeur vers la structure de jeu (`t_game`).
 * @param clean_line Chaîne nettoyée (trimmed) de la ligne entière
 * (ex. "F 220,100,0").
 * @param color_str  Portion après « F » ou « C » (ex. "220,100,0").
 * @param parser     Pointeur vers la structure `t_parser`.
 */
bool	parse_color(t_game *game, char *clean_line,
		char *color_str, t_parser *parser)
{
	char	**tokens;
	bool	success;

	if (!game || !clean_line || !color_str || !parser)
		return (false);
	if (!check_commas(color_str))
		return (false);
	tokens = split_and_validate_color(color_str);
	if (!tokens)
		return (false);
	if (!ft_strncmp(clean_line, "F ", 2))
		success = assign_color(game->config.floor_color, tokens, parser);
	else if (!ft_strncmp(clean_line, "C ", 2))
		success = assign_color(game->config.ceiling_color, tokens, parser);
	else
		success = false;
	free_split(tokens);
	return (success);
}
