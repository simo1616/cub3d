/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:23:35 by mbendidi          #+#    #+#             */
/*   Updated: 2025/04/09 16:40:31 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void	check_first_or_last_line(char *line, t_parser *parser)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] != '1')
				exit_text_with_error(ERR_MAP_FIRST_LAST_LINE, parser);
			i++;
		}
		while (line[i] == ' ' || line[i] == '\t')
			i++;
	}
}

void	check_line_borders(char *line, t_line_info info, t_parser *parser)
{
	if (is_only_spaces(line))
	{
		ft_putstr_fd("Error\nLigne : ", 2);
		ft_putnbr_fd(info.row, 2);
		ft_putstr_fd(" vide ou que des espaces.\n", 2);
		exit_text_with_error("", parser);
	}
	if (info.row == info.first || info.row == info.last)
		check_first_or_last_line(line, parser);
	else
		check_middle_line(line, info.row, parser);
}

bool	dfs_closed(t_mapinfo *info, int r, int c)
{
	if (r < 0 || r >= info->height || c < 0 || c >= info->width)
		return (false);
	if (info->visited[r][c] || info->map2d[r][c] == '1')
		return (true);
	info->visited[r][c] = true;
	if (!dfs_closed(info, r - 1, c))
		return (false);
	if (!dfs_closed(info, r + 1, c))
		return (false);
	if (!dfs_closed(info, r, c - 1))
		return (false);
	if (!dfs_closed(info, r, c + 1))
		return (false);
	return (true);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}
