/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:36:12 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 16:12:17 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cub3d.h"

void	cleanup_get_next_line(void)
{
	get_next_line(-42);
}

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
