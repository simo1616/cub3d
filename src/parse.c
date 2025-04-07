#include "cub3d.h"

int	ft_parse(t_game *game, char *file_name)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	*clean_line;
	int		match_text;
	int		match_color;
	bool	map_is_done;
	bool    empty_line_after_map;
	bool    map_started; 
	
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nImpossible d'ouvrir le fichier: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	match_text = 0;
	match_color = 0;
	empty_line_after_map = false;
	map_started = false; 
	map_is_done = false;
	game->map = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		clean_line = ft_strtrim(line, " \t\n");
		if (clean_line && ft_strlen(clean_line) > 0)
		{
			if (!ft_strncmp(clean_line, "NO ", 3) || !ft_strncmp(clean_line, "SO ", 3) ||
				!ft_strncmp(clean_line, "WE ", 3) || !ft_strncmp(clean_line, "EA ", 3))
			{
				match_text = 1;
				trimmed = ft_strtrim(clean_line + 3, " \t\n");
				if (trimmed == NULL)
				{
					ft_putstr_fd("Error\nÉchec de l'allocation mémoire pour textures.\n", 2);
					free(clean_line);
					free(line);
					exit(EXIT_FAILURE);
				}
				if (ft_strlen(trimmed) == 0)
				{
					ft_putstr_fd("Error\nChemin de texture vide.\n", 2);
					free(trimmed);
					free(clean_line);
					free(line);
					exit(EXIT_FAILURE);
				}
				check_access(trimmed, clean_line);
				if (!ft_strncmp(clean_line, "NO ", 3))
				{
					if (game->config.no_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture NO déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
					game->config.no_textures = ft_strdup(trimmed);
					if (game->config.no_textures == NULL)
					{
						ft_putstr_fd("Error\nÉchec de l'allocation mémoire pour texture NO.\n", 2);
						free(trimmed);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(clean_line, "SO ", 3))
				{
					if (game->config.so_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture SO déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
					game->config.so_textures = ft_strdup(trimmed);
					if (game->config.so_textures == NULL)
					{
						ft_putstr_fd("Error\nTexture SO déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(clean_line, "WE ", 3))
				{
					if (game->config.we_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture WE déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
					game->config.we_textures = ft_strdup(trimmed);
					if (game->config.we_textures == NULL)
					{
						ft_putstr_fd("Error\nTexture WE déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(clean_line, "EA ", 3))
				{
					if (game->config.ea_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture EA déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
					game->config.ea_textures = ft_strdup(trimmed);
					if (game->config.ea_textures == NULL)
					{
						ft_putstr_fd("Error\nTexture EA déjà définie.\n", 2);
						free(clean_line);
						free(line);
						exit(EXIT_FAILURE);
					}
				}
				free(trimmed);
			}
			else if (!ft_strncmp(clean_line, "F ", 2) ||
					 !ft_strncmp(clean_line, "C ", 2))
			{
				match_color = 1;
				trimmed = ft_strtrim(clean_line + 2, " \t\n");
				if (!trimmed)
				{
					ft_putstr_fd("Error\nÉchec de l'allocation mémoire pour couleur.\n", 2);
					free(clean_line);
					free(line);
					close(fd);
					exit(EXIT_FAILURE);
				}
				parse_color(game, clean_line, trimmed);
				free(trimmed);
				//free(clean_line);
				//free(line);
			}
			else
			{
				if (map_is_done)
				{
						ft_putstr_fd("Error\nDes données supp après la carte.\n", 2);
						free(clean_line);
						free(line);
						close(fd);
						exit(EXIT_FAILURE);
				}
				else if (empty_line_after_map)
				{
						ft_putstr_fd("Error\nDes caractères trouvés après des lignes vides suivant la carte.\n", 2);
						free(clean_line);
						free(line);
						close(fd);
						exit(EXIT_FAILURE);
				}
				else
				{
						if (!match_text || !match_color)
						{
								ft_putstr_fd("Error\nPosition de la map incorrecte (pas toutes les textures/couleurs lues).\n", 2);
								free(clean_line);
								free(line);
								close(fd);
								exit(EXIT_FAILURE);
						}
						map_started = true;
						append_map_line(game, ft_strtrim(line, "\n"));
				}
				
			}
		}
		else
		{
				if (map_started)
				{
						map_is_done = true;
						empty_line_after_map = true;
				}
		}
		free(clean_line);
		free(line);
	}
	check_validate_map(game);
	final_check_config(game);
	close(fd);
	return (0);
}
