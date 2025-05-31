/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:35 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:23:49 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Vérifie si une ligne de la map ne contient que 
 * des espaces ou tabulations.
 *
 * - Parcourt `line[i]` tant que `line[i] == ' '` ou `'\t'`.
 * - Si rencontre un autre caractère, renvoie false.
 *
 * @param line Chaîne à tester.
 * @return bool true si uniquement espaces/tabs, false sinon.
 */
bool	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Vérifie que la première ou la dernière ligne 
 * de la map est uniquement composée de '1'.
 *
 * - Parcourt `line` après avoir sauté espaces/tabs initiaux.
 * - Pour chaque groupe de caractères non-blancs, 
 * si ce n’est pas '1', 
 * appelle `exit_text_with_error(ERR_MAP_FIRST_LAST_LINE, parser)`.
 *
 * @param line   Chaîne de la ligne (map).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	check_first_or_last_line(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] != '1')
				exit_text_with_error(ERR_MAP_FIRST_LAST_LINE, parser);
			i++;
		}
		while (line[i] == ' ' || line[i] == '\t')
			i++;
	}
}

/**
 * @brief Vérifie la bordure d’une ligne donnée (première, dernière ou middle).
 *
 * - Si `is_only_spaces(line)` : 
 *   - Affiche `"Error\nLigne : <row> vide ou que des espaces.\n"` 
 *  	puis `exit_text_with_error`.
 * - Si `row == first || row == last` : 
 * appelle `check_first_or_last_line(line, parser)`.
 * - Sinon : appelle `check_middle_line(line, row, parser)`.
 *
 * @param line   Chaîne de la ligne (map).
 * @param info   Structure `t_line_info` contenant `row`, `first`, `last`.
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	check_line_borders(char *line, t_line_info info, t_parser *parser)
{
	if (is_only_spaces(line))
	{
		ft_putstr_fd("Error\nLigne : ", 2);
		ft_putnbr_fd(info.row, 2);
		ft_putstr_fd(" vide ou que des espaces.\n", 2);
		exit_text_with_error("", parser);
	}
	if (info.row == info.first || info.row == info.last)
		check_first_or_last_line(line, parser);
	else
		check_middle_line(line, info.row, parser);
}

/**
 * @brief Effectue une recherche en profondeur 
 * pour vérifier que la map est fermée.
 *
 * - Si `(r,c)` hors bornes, renvoie false (fuite).
 * - Si `visited[r][c] == true` ou `map2d[r][c] == '1'`, 
 * 		renvoie true (mur ou déjà visité).
 * - Marque `visited[r][c] = true`.
 * - Appelle récursivement pour (r-1,c), (r+1,c), (r,c-1), (r,c+1). 
 * 		Si un appel renvoie false, retourne false.
 * - Sinon, retourne true.
 *
 * @param info Pointeur vers `t_mapinfo` 
 * (contient `map2d`, `visited`, `height`, `width`).
 * @param r    Coordonnée Y courante dans la map.
 * @param c    Coordonnée X courante dans la map.
 * @return bool true si la zone est fermée, 
 * false si une fuite détectée.
 */
bool	dfs_closed(t_mapinfo *info, int r, int c)
{
	if (r < 0 || r >= info->height || c < 0 || c >= info->width)
		return (false);
	if (info->visited[r][c] || info->map2d[r][c] == '1')
		return (true);
	info->visited[r][c] = true;
	if (!dfs_closed(info, r - 1, c))
		return (false);
	if (!dfs_closed(info, r + 1, c))
		return (false);
	if (!dfs_closed(info, r, c - 1))
		return (false);
	if (!dfs_closed(info, r, c + 1))
		return (false);
	return (true);
}

/**
 * @brief Vérifie qu’un caractère est valide pour la map (0,1,N,S,E,W ou espace).
 *
 * @param c Caractère à tester.
 * @return bool true si c ∈ {'0','1','N','S','E','W',' '}, false sinon.
 */
bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}
