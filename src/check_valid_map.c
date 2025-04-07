#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static bool is_only_spaces(char *line)
{
	int i;
 
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return false;
		i++;
	}
	return true;
}

static void check_first_or_last_line(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;

	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] != '1')
			{
				ft_putstr_fd("Error\nLigne %d (1ère/dernière) contient autre chose que '1'.\n", 2);
				exit(EXIT_FAILURE);
			}
			i++;
		}

		while (line[i] == ' ' || line[i] == '\t')
			i++;
	}
}

static void check_middle_line(char *line, int row)
{
	int i;
	int end;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;

	if (line[i] != '1')
	{
		ft_putstr_fd("Error\nLigne %d ne commence pas par un mur '1'.\n", 2);
		exit(EXIT_FAILURE);
	}

	end = (int)strlen(line) - 1;
	while (end >= 0 && (line[end] == ' ' || line[end] == '\t'))
		end--;

	if (end < 0)
	{
		ft_putstr_fd("Error\nLigne : ", 2);
		ft_putnbr_fd(row, 2);
		ft_putstr_fd(" est vide.\n", 2);
		exit(EXIT_FAILURE);
	}

	if (line[end] != '1')
	{
		ft_putstr_fd("Error\nLigne : ", 2);
		ft_putnbr_fd(row, 2);
		ft_putstr_fd(" ne finit pas par un mur '1'.\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void check_line_borders( char *line, int row, int first, int last)
{
	if (is_only_spaces(line))
	{
		ft_putstr_fd("Error\nLigne : ", 2);
		ft_putnbr_fd(row, 2);
		ft_putstr_fd(" vide ou que des espaces.\n", 2);
		exit(EXIT_FAILURE);
	}

	if (row == first || row == last)
		check_first_or_last_line(line);
	else
		check_middle_line(line, row);
}



static bool dfs_closed(t_mapinfo *info, int r, int c)
{
	if (r < 0 || r >= info->height || c < 0 || c >= info->width)
		return false;

	if (info->visited[r][c] || info->map2d[r][c] == '1')
		return true;

	info->visited[r][c] = true;

	if (!dfs_closed(info, r - 1, c)) return false;
	if (!dfs_closed(info, r + 1, c)) return false;
	if (!dfs_closed(info, r, c - 1)) return false;
	if (!dfs_closed(info, r, c + 1)) return false;

	return true;
}

static bool is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

void	check_validate_map(t_game *game)
{
	int			height;
	int			row;
	int			last;
	int			width;
	int			i;
	int			len;
	t_mapinfo	info;
	int			r;
	int			c;
	int			player_count;
	int			player_r;
	int			player_c;
	char		ch;

	height = 0;
	if(game->map)
	{
		while (game->map[height])
			height++;
	}
	if (height == 0)
	{
		ft_putstr_fd("Error\nMap vide.\n", 2);
		exit(EXIT_FAILURE);
	}
	last = height - 1;
	row = 0;
	while (row < height)
	{
		check_line_borders(game->map[row], row, 0, last);
		row++;
	}

	width = 0;
	i = 0;
	while (i < height)
	{
		len = (int)strlen(game->map[i]);
		if (len > width)
			width = len;
		i++;
	}

	info.height = height;
	info.width = width;

	info.map2d = (char **)malloc(sizeof(char *) * height);
	if (!info.map2d)
	{
		ft_putstr_fd("Error\nMalloc failed for map2d.\n", 2);
		exit(EXIT_FAILURE);
	}

	r = 0;
	while (r < height)
	{
		info.map2d[r] = (char *)malloc(sizeof(char) * (width + 1));
		if (!info.map2d[r])
		{
			ft_putstr_fd("Error\nMalloc failed for map2d row.\n", 2);
			exit(EXIT_FAILURE);
		}

		c = 0;
		len = (int)strlen(game->map[r]);
		while (c < len)
		{
			info.map2d[r][c] = game->map[r][c];
			c++;
		}
		while (c < width)
		{
			info.map2d[r][c] = ' ';
			c++;
		}
		info.map2d[r][width] = '\0';
		r++;
	}

	player_count = 0;
	player_r = -1;
	player_c = -1;

	r = 0;
	while (r < height)
	{
		c = 0;
		while (c < width)
		{
			ch = info.map2d[r][c];
			if (!is_valid_map_char(ch))
			{
				ft_putstr_fd("Error\nCaractère invalide.\n", 2);
				exit(EXIT_FAILURE);
			}
			if (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
			{
				player_count++;
				player_r = r;
				player_c = c;
				info.map2d[r][c] = '0';
			}
			c++;
		}
		r++;
	}

	if (player_count != 1)
	{
		ft_putstr_fd("Error\nIl faut exactement 1 orientation (N,S,E,W). Trouvé: ", 2);
		ft_putstr_fd("player_count", 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}

	info.visited = (bool **)malloc(sizeof(bool *) * height);
	if (!info.visited)
	{
		ft_putstr_fd("Error\nMalloc failed for visited.\n", 2);
		exit(EXIT_FAILURE);
	}

	r = 0;
	while (r < height)
	{
		info.visited[r] = (bool *)calloc(width, sizeof(bool));
		if (!info.visited[r])
		{
			ft_putstr_fd("Error\nMalloc failed for visited row.\n", 2);
			exit(EXIT_FAILURE);
		}
		r++;
	}

	if (!dfs_closed(&info, player_r, player_c))
	{
		ft_putstr_fd("Error\nMap non fermée (fuite détectée)\n", 2);
		exit(EXIT_FAILURE);
	}
	r = 0;
	while (r < height)
	{
		free(info.map2d[r]);
		free(info.visited[r]);
		r++;
	}
	free(info.map2d);
	free(info.visited);
}

