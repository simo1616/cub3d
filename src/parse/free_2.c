/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:36:12 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 18:54:31 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Appelle `get_next_line(-42)` pour vider le buffer interne.
 *
 * - Nécessaire après la fin de la lecture de la file dans le parsing.
 */
void	cleanup_get_next_line(void)
{
	get_next_line(-42);
}

/**
 * @brief Libère un tableau de chaînes et chaque chaîne à l’intérieur.
 *
 * - Pour chaque `tokens[i] != NULL`, appelle `free(tokens[i])`, puis
 *   `free(tokens)`.
 *
 * @param tokens Tableau de chaînes à libérer.
 */
void	free_split(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
