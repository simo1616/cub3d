/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:52 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 12:20:13 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit_game(t_game *game, char *msg)
{
	ft_putstr_fd(msg, 2);
	cleanup_before_exit(game);
	exit(EXIT_FAILURE);
}

void	exit_text_with_error(char *msg, t_parser *parser)
{
	ft_putstr_fd(msg, 2);
	cleanup_all(parser->game, parser);
	free(parser->state);
	exit(EXIT_FAILURE);
}

void	error_and_exit(t_parser *parser, char *msg)
{
	ft_putstr_fd(msg, 2);
	cleanup_get_next_line();
	cleanup_all(parser->game, parser);
	free(parser->state);
	exit(EXIT_FAILURE);
}

void	error_and_exit_free(t_parser *parser, char **tokens, char *msg)
{
	free_split(tokens);
	ft_putstr_fd(msg, 2);
	cleanup_get_next_line();
	cleanup_all(parser->game, parser);
	free(parser->state);
	exit(EXIT_FAILURE);
}

void	check_color_value(int value, t_parser *parser)
{
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("Error:\nCouleur invalide: ", 2);
		ft_putnbr_fd(value, 2);
		ft_putchar_fd('\n', 2);
		exit_text_with_error("", parser);
	}
}
