/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 19:18:05 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ft_putstr_fd(
			"Error\nFichier invalide : extension '.cub' requise\n", 2);
		return (-1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(ERR_OPEN_FILE, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
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
 *   appelle `cleanup_all` et `exit(EXIT_FAILURE)`.
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
		ft_putstr_fd("Error\nfichier de texture inaccessible: ", 2);
		ft_putstr_fd(trimmed, 2);
		cleanup_all(parser->game, parser);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
