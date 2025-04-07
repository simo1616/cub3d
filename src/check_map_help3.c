/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:35 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/07 21:55:58 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_line_error_empty(int row)
{
	ft_putstr_fd("Error\nLigne : ", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd(" est vide.\n", 2);
	exit(EXIT_FAILURE);
}

static void	print_line_error_end(int row)
{
	ft_putstr_fd("Error\nLigne : ", 2);
	ft_putnbr_fd(row, 2);
	ft_putstr_fd(" ne finit pas par un mur '1'.\n", 2);
	exit(EXIT_FAILURE);
}

static void	check_line_starts_with_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '1')
	{
		ft_putstr_fd(ERR_MAP_START_LINE, 2);
		exit(EXIT_FAILURE);
	}
}

static void	check_line_ends_with_wall(char *line, int row)
{
	int	end;

	end = (int)strlen(line) - 1;
	while (end >= 0 && (line[end] == ' ' || line[end] == '\t'))
		end--;
	if (end < 0)
		print_line_error_empty(row);
	if (line[end] != '1')
		print_line_error_end(row);
}

void	check_middle_line(char *line, int row)
{
	check_line_starts_with_wall(line);
	check_line_ends_with_wall(line, row);
}
