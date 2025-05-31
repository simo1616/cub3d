/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:12 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:53:52 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
 * @param parser Pointeur vers la structure `t_parser`.
 * @return char** Tableau de 3 chaînes (tokens), 
 * ou ne retourne pas en cas d’erreur.
 */
static char	**split_and_validate_color(char *str, t_parser *parser)
{
	char	**tokens;
	int		count;
	int		i;

	tokens = ft_split(str, ',');
	if (!tokens)
		error_and_exit(parser, ERR_MEM_ALLOC_COLOR);
	count = 0;
	while (tokens[count])
		count++;
	if (count != 3)
		error_and_exit_free(parser, tokens, ERR_INVALID_COLOR_FORMAT);
	i = 0;
	while (i < 3)
	{
		if (!tokens[i])
			error_and_exit_free(parser, tokens,
				"Error\nFormat de couleur invalide\n");
		i++;
	}
	return (tokens);
}

/**
 * @brief Assigne les valeurs numériques parsed dans `tokens[]` à `target[0..2]`.
 *
 * - Si `target[0] != -1` déjà défini, libère tokens et 
 *   `error_and_exit_free(parser, tokens, "Couleur déjà définie\n")`.
 * - Pour i de 0 à 2, `target[i] = ft_atoi(tokens[i])` 
 *   puis `check_color_value(target[i], parser)`.
 *
 * @param target Pointeur vers le tableau de 3 entiers 
 * (floor_color ou ceiling_color).
 * @param tokens Tableau de 3 chaînes numériques (r,g,b).
 * @param parser Pointeur vers la structure `t_parser`.
 */
static void	assign_color(int *target, char **tokens, t_parser *parser)
{
	int	i;

	if (target[0] != -1)
		error_and_exit_free(parser, tokens, "Error\nCouleur déjà définie.\n");
	i = 0;
	while (i < 3)
	{
		target[i] = ft_atoi(tokens[i]);
		check_color_value(target[i], parser);
		i++;
	}
}

/**
 * @brief Parse une ligne de couleur (clean_line commence par "F " ou "C ").
 *
 * - Scinde `color_str` (chaine après « F » ou « C ») 
 * 	 via `split_and_validate_color`.
 * - Si `clean_line` commence par "F ", 
 * 	 appelle `assign_color(game->config.floor_color,…)`.
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
void	parse_color(t_game *game, char *clean_line, char *color_str,
		t_parser *parser)
{
	char	**tokens;

	tokens = split_and_validate_color(color_str, parser);
	if (!ft_strncmp(clean_line, "F ", 2))
		assign_color(game->config.floor_color, tokens, parser);
	else if (!ft_strncmp(clean_line, "C ", 2))
		assign_color(game->config.ceiling_color, tokens, parser);
	else
	{
		free_split(tokens);
		error_and_exit(parser, ERR_UNKNOWN_COLOR_IDENTIFIER);
	}
	free_split(tokens);
}
