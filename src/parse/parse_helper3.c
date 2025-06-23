/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:32:12 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 18:33:00 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Détecte si la ligne est une définition de texture.
 *
 * Retourne true si elle commence par NO, SO, WE ou EA.
 */
bool	is_texture_attempt(char *line)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0)
		return (true);
	return (false);
}

/**
 * @brief Valide le format minimal d’une ligne de texture.
 *
 * - au moins 4 caractères
 * - code suivi d’espace et d’un chemin non vide
 */
bool	is_valid_texture_format(char *line)
{
	char	*path;

	if (!line || ft_strlen(line) < 4)
		return (false);
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
	{
		path = ft_strtrim(line + 3, " \t");
		if (path && *path)
		{
			free(path);
			return (true);
		}
		free(path);
	}
	return (false);
}

/**
 * @brief Détecte si la ligne est une définition de couleur.
 *
 * Retourne true si elle commence par F ou C.
 */
bool	is_color_attempt(char *line)
{
	if (!line)
		return (false);
	if (line[0] == 'F' || line[0] == 'C')
		return (true);
	return (false);
}

/**
 * @brief Valide le format minimal d’une ligne de couleur.
 *
 * - au moins 3 caractères
 * - code suivi d’espace et d’au moins un octet
 */
bool	is_valid_color_format(char *line)
{
	char	*values;

	if (!line || ft_strlen(line) < 3)
		return (false);
	if (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
	{
		values = ft_strtrim(line + 2, " \t");
		if (values && *values)
		{
			free(values);
			return (true);
		}
		free(values);
	}
	return (false);
}

/**
 * @brief Vérifie si une ligne appartient à la map.
 *
 * Autorise '0','1', espaces, tabs, N/S/E/W après indentation.
 */
bool	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (false);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != ' ' && line[i] != '\t'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}
