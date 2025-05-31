/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:23 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:49:49 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Compte le nombre de lignes actuellement 
 * dans la map (tableau de chaînes).
 *
 * @param map Tableau de chaînes (char **).
 * @return int Nombre de lignes (jusqu’au premier NULL).
 */
static int	count_lines(char **map)
{
	int	cnt;

	cnt = 0;
	while (map && map[cnt])
		cnt++;
	return (cnt);
}

/**
 * @brief Alloue un nouveau tableau `new_map` de taille (count+2) 
 * et copie `old_map`.
 *
 * - Copie chaque pointeur `old_map[i]` dans `new_map[i]`.
 * - Place `new_map[count] = NULL` puis libère `old_map`.
 * - Vérifie l’allocation : si échoue, affiche `ERR_MAP_MALLOC` 
 * 	 et `exit(EXIT_FAILURE)`.
 *
 * @param old_map Ancienne map (char **), peut être NULL.
 * @param count   Nombre de lignes dans `old_map`.
 * @return char** Nouveau tableau de chaînes, prêt à recevoir une nouvelle ligne.
 */
static char	**alloc_and_copy(char **old_map, int count)
{
	int		i;
	char	**new_map;

	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
	{
		ft_putstr_fd(ERR_MAP_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (old_map && old_map[i])
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = NULL;
	if (old_map)
		free(old_map);
	return (new_map);
}

/**
 * @brief Ajoute une ligne à la fin de `game->map`.
 *
 * - Calcule `count = count_lines(game->map)`.
 * - Alloue un nouveau tableau de taille count+2 via `alloc_and_copy`.
 * - Copie `cpy_line` dans `new_map[count]`, place NULL dans `new_map[count+1]`.
 * - Met à jour `game->map = new_map`.
 *
 * @param game     Pointeur vers la structure de jeu (`t_game`).
 * @param cpy_line Chaîne déjà allouée (with '\n' trimmé) à ajouter.
 */
void	append_map_line(t_game *game, char *cpy_line)
{
	int		count;
	char	**new_map;

	count = count_lines(game->map);
	new_map = alloc_and_copy(game->map, count);
	new_map[count] = cpy_line;
	new_map[count + 1] = NULL;
	game->map = new_map;
}
