/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:12 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/08 16:38:43 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**split_and_validate_color(char *str)
{
	char	**tokens;
	int		count;
	int		i;

	tokens = ft_split(str, ',');
	if (!tokens)
		error_and_exit(ERR_MEM_ALLOC_COLOR);
	count = 0;
	while (tokens[count])
		count++;
	if (count != 3)
		error_and_exit_free(tokens, ERR_INVALID_COLOR_FORMAT);
	i = 0;
	while (i < 3)
	{
		if (!tokens[i])
			error_and_exit_free(tokens, "Error\nFormat de couleur invalide\n");
		i++;
	}
	return (tokens);
}

static void	assign_color(int *target, char **tokens, t_parser *parser)
{
	int	i;

	if (target[0] != -1)
		error_and_exit_free(tokens, "Error\nCouleur déjà définie.\n");
	i = 0;
	while (i < 3)
	{
		target[i] = ft_atoi(tokens[i]);
		check_color_value(target[i], parser);
		i++;
	}
}

void	parse_color(t_game *game, char *clean_line, char *color_str, t_parser *parser)
{
	char	**tokens;

	tokens = split_and_validate_color(color_str);
	if (!ft_strncmp(clean_line, "F ", 2))
		assign_color(game->config.color_sol, tokens, parser);
	else if (!ft_strncmp(clean_line, "C ", 2))
		assign_color(game->config.color_plafond, tokens, parser);
	else
	{
		free_split(tokens);
		error_and_exit(ERR_UNKNOWN_COLOR_IDENTIFIER);
	}
	free_split(tokens);
}
