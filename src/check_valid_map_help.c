#include "cub3d.h"

bool is_only_spaces(char *line)
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

void check_first_or_last_line(char *line)
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

void check_middle_line(char *line, int row)
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

void check_line_borders( char *line, int row, int first, int last)
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



bool dfs_closed(t_mapinfo *info, int r, int c)
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

bool is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}
