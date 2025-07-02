/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/07/02 12:00:41 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Traite un caractère `ch` de la map pour compter le joueur éventuel.
 *
 * - Si `ch` invalide (pas '0'/'1'/'N'/'S'/'E'/'W'/' '),
 * appelle `error_and_exit`.
 * - Si `ch ∈ {'N','S','E','W'}` :
 * incrémente `*d->count`, stocke `*d->row = r`, `*d->col = c`,
 *   remplace `info->map2d[r][c]` par '0'.
 *
 * @param ch Char soit '0'/'1'/'N'/'S'/'E'/'W'/' '.
 * @param r  Ligne courante (index).
 * @param c  Colonne courante (index).
 * @param d  Pointeur vers `t_player_data`
 * (contient count, row, col, info, parser).
 */
void	store_player(char ch, int r, int c, t_player_data *d)
{
	if (!is_valid_map_char(ch))
	{
		free_mapinfo(d->info);
		if (d->parser && d->parser->state)
			d->parser->state->mapinfo = NULL;
		error_and_exit(d->parser, ERR_MAP_INVALID_CHAR);
	}
	if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
	{
		(*d->count)++;
		*d->row = r;
		*d->col = c;
		d->info->map2d[r][c] = '0';
	}
}

/**
 * @brief Ouvre un fichier `.cub` après vérification d’extension.
 *
 * - `len = strlen(file_name)`. Si `len < 4` 
 * ou `file_name[len-4..] != ".cub"`,
 *   affiche `"Error\nFichier invalide : extension '.cub' requise\n"`, 
 * retourne -1.
 * - Appelle `open(file_name, O_RDONLY)`. Si `fd == -1`, 
 * affiche `ERR_OPEN_FILE` + `file_name`, retourne -1.
 * - Sinon, retourne le descripteur `fd`.
 *
 * @param file_name Nom du fichier .cub à ouvrir.
 * @return int Descripteur de fichier (>= 0) ou -1 en cas d’erreur.
 */
int	open_map_file(char *file_name)
{
	int		fd;
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strcmp(file_name + len - 4, ".cub") != 0)
	{
		ft_putstr_fd(ERR_EXTENSION_INVALID, 2);
		return (-1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(ERR_OPEN_FILE, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (fd);
}

/**
 * @brief Vérifie que la chaîne `str` ne comporte que des chiffres.
 *
 * - Parcourt `str[i]` tant que `isdigit(str[i])` est vrai.
 * - Si rencontre un caractère non numérique, renvoie 0.
 * - Sinon renvoie 1.
 *
 * @param str Chaîne à tester.
 * @return int 1 si tous les caractères sont des chiffres, 0 sinon.
 */
int	is_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Vérifie l’accès (read-only) à un fichier de texture.
 *
 * - `fd = open(parser->trimmed, O_RDONLY)`. Si `fd == -1` ou 
 *   la fin de `trimmed` n’est pas “.xpm”, affiche  
 *   `"Error\nfichier de texture inaccessible: " + trimmed`, 
 *   appelle `cleanup_all_safe` et `exit(EXIT_FAILURE)`.
 * - Sinon, `close(fd)`.
 *
 * @param parser Pointeur vers la structure `t_parser` 
 * (contient `trimmed` et `game`).
 */
void	check_access(t_parser *parser)
{
	int		fd;
	char	*trimmed;

	trimmed = parser->trimmed;
	fd = open(trimmed, O_RDONLY);
	if (fd == -1 || ft_strcmp(trimmed + ft_strlen(trimmed) - 4, ".xpm"))
	{
		ft_putstr_fd(ERR_FILE_TEXT_INACCESSIBLE, 2);
		ft_putstr_fd(trimmed, 2);
		ft_putstr_fd("\n", 2);
		cleanup_get_next_line();
		cleanup_all(parser->game, parser);
		if (fd != -1)
			close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
