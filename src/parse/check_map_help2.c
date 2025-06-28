/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:37:02 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/27 21:34:19 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Alloue et initialise la matrice `visited`
 *  de taille [height][width].
 *
 * - `info->visited = malloc(sizeof(bool*) * info->height)`.
 * - Pour chaque rangée r ∈ [0..height-1],
 *   alloue `calloc(info->width, sizeof(bool))`.
 * - Si échec d’allocation, appelle
 *  `error_and_exit(parser, ERR_MAP_MALLOC)`.
 *
 * @param info   Pointeur vers la structure `t_mapinfo` (
 * contient `height`, `width`).
 * @param parser Pointeur vers la structure `t_parser`.
 */
void	init_visited_map(t_mapinfo *info, t_parser *parser)
{
	int	r;

	info->visited = malloc(sizeof(bool *) * info->height);
	if (!info->visited)
		error_and_exit(parser, ERR_MAP_MALLOC);
	r = 0;
	while (r < info->height)
	{
		info->visited[r] = calloc(info->width, sizeof(bool));
		if (!info->visited[r])
			error_and_exit(parser, ERR_MAP_MALLOC);
		r++;
	}
}

/**
 * @brief Libère la structure `mapinfo` (map2d et visited).
 *
 * - Pour chaque rangée r ∈ [0..height-1] :
 *  `free(info->map2d[r])`, `free(info->visited[r])`.
 * - `free(info->map2d)`, `free(info->visited)`.
 *
 * @param info Pointeur vers la structure `t_mapinfo`.
 */
void	free_mapinfo(t_mapinfo *info)
{
	if (info->map2d)
		free_2d_array((void **)info->map2d, info->height);
	if (info->visited)
		free_2d_array((void **)info->visited, info->height);
	info->map2d = NULL;
	info->visited = NULL;
	info->height = 0;
	info->width = 0;
}

/**
 * @brief Calcule la hauteur de la map (nombre de lignes) à partir de `map`.
 *
 * @param map Tableau de chaînes (char **).
 * @return int Nombre de lignes jusqu’au NULL.
 */
int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

/**
 * @brief Vérifie que la map n’est pas vide (height == 0).
 *
 * - Si `height == 0`, affiche `ERR_MAP_EMPTY` sur stderr
 * et `exit(EXIT_FAILURE)`.
 *
 * @param height Hauteur de la map (nombre de lignes).
 */
void	check_map_empty(int height)
{
	if (height == 0)
	{
		ft_putstr_fd(ERR_MAP_EMPTY, 2);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Calcule la largeur maximale (nombre de colonnes)
 * parmi les lignes de `map`.
 *
 * - Parcourt i ∈ [0..height-1], `len = strlen(map[i])`.
 * Si `len > width`, met à jour.
 *
 * @param map    Tableau de chaînes (char **).
 * @param height Nombre de lignes de `map`.
 * @return int   Largeur maximale trouvée.
 */
int	get_max_width(char **map, int height)
{
	int	i;
	int	len;
	int	width;

	width = 0;
	i = 0;
	while (i < height)
	{
		len = (int)ft_strlen(map[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}
