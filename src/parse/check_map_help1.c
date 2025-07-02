/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:35 by mbendidi          #+#    #+#             */
/*   Updated: 2025/07/02 12:03:29 by mbendidi         ###   ########.fr       */
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
