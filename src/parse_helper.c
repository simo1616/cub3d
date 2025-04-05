#include "cub3d.h"

int is_integer(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}

void check_access(char *trimmed, char *clean_line)
{
	int fd;

	fd = open(trimmed, O_RDONLY);
	if(fd == -1)
	{
		ft_putstr_fd("Error\nfichier de texture inaccessible: ", 2);
		ft_putstr_fd(trimmed, 2);
		free(trimmed);
		free(clean_line);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void final_check_config(t_game *game, int len)
{
	if(game)
	{
		if(!game->config.no_textures)
		{
			ft_putstr_fd("Error\nTexture NO non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		else if(!game->config.so_textures)
		{
			ft_putstr_fd("Error\nTexture SO non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		else if(!game->config.ea_textures)
		{
			ft_putstr_fd("Error\nTexture EA non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		else if(!game->config.we_textures)
		{
			ft_putstr_fd("Error\nTexture WE non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		else if(game->config.color_sol[0] == -1)
		{
			ft_putstr_fd("Error\nColeur F(Sol) non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		else if(game->config.color_plafond[0] == -1)
		{
			ft_putstr_fd("Error\nColeur C(Plaf.) non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		else if(!game->map)
		{
			ft_putstr_fd("Error\nmap non définie.\n", 2);
			exit(EXIT_FAILURE);
		}
		
	}
	if (len > 1)
		check_valid_first_last_line(game, len);
	else
	{
		ft_putstr_fd("Error:\n Map not complete.\n", 2);
		exit(EXIT_FAILURE);
	}
}
