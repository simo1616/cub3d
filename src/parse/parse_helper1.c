/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:24:16 by mbendidi          #+#    #+#             */
/*   Updated: 2025/05/31 14:23:59 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
