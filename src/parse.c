#include "cub3d.h"

static void	parse_color(t_game *game, char *clean_line, char *color_str)
{
	char	**tokens;
	int		tok_cnt;
	int		i;

	tokens = ft_split(color_str, ',');
	if (!tokens)
		error_and_exit(ERR_MEM_ALLOC_COLOR);
	tok_cnt = 0;
	while(tokens[tok_cnt])
		tok_cnt++;
	if(tok_cnt != 3)
		error_and_exit_free(tokens, ERR_INVALID_COLOR_FORMAT);
	i = 0;
	while (i < 3)
	{
		if (!tokens[i])
			error_and_exit_free(tokens, "Format de couleur invalide\n");
		i++;
	}
	i = 0;
	if (!ft_strncmp(clean_line, "F ", 2))
	{
		if (game->config.color_sol[0] != -1)
		{
			printf("%ls\n", game->config.color_plafond);
			printf("%ls\n", game->config.color_sol);
			ft_putstr_fd("Error\n =====Couleur déjà définie.\n", 2);
			free(clean_line);
			exit(EXIT_FAILURE);
		}
		while (i < 3)
		{
			game->config.color_sol[i] = ft_atoi(tokens[i]);
			check_color_value(game->config.color_sol[i]);
			i++;
		}
	}
	else if (!ft_strncmp(clean_line, "C ", 2))
	{
		if (game->config.color_plafond[0] != -1)
		{
			printf("%ls\n", game->config.color_plafond);
			printf("%ls\n", game->config.color_sol);
			ft_putstr_fd("Error\n =====Couleur déjà définie.\n", 2);
			free(clean_line);
			exit(EXIT_FAILURE);
		}
		while (i < 3)
		{
			game->config.color_plafond[i] = ft_atoi(tokens[i]);
			check_color_value(game->config.color_plafond[i]);
			i++;
		}
	}
	else
	{
		free_split(tokens);
		error_and_exit(ERR_UNKNOWN_COLOR_IDENTIFIER);
	}
	free_split(tokens);
}

int	ft_parse(t_game *game, char *file_name)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	*clean_line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nImpossible d'ouvrir le fichier: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		clean_line = ft_strtrim(line, " \t\n");
		free(line);
		if (clean_line && ft_strlen(clean_line) > 0)
		{
			if (!ft_strncmp(clean_line, "NO ", 3) || !ft_strncmp(clean_line, "SO ", 3) ||
				!ft_strncmp(clean_line, "WE ", 3) || !ft_strncmp(clean_line, "EA ", 3))
			{
				trimmed = ft_strtrim(clean_line + 3, " \t\n");
				if (trimmed == NULL)
				{
					ft_putstr_fd("Error\nÉchec de l'allocation mémoire pour textures.\n", 2);
					free(clean_line);
					exit(EXIT_FAILURE);
				}
				if (ft_strlen(trimmed) == 0)
				{
					ft_putstr_fd("Error\nChemin de texture vide.\n", 2);
					free(trimmed);
					free(clean_line);
					exit(EXIT_FAILURE);
				}
				check_access(trimmed, clean_line);
				/////////////////
				if (!ft_strncmp(clean_line, "NO ", 3))
				{
					if (game->config.no_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture NO déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
					game->config.no_textures = ft_strdup(trimmed);
					if (game->config.no_textures == NULL)
					{
						ft_putstr_fd("Error\nÉchec de l'allocation mémoire pour texture NO.\n", 2);
						free(trimmed);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(clean_line, "SO ", 3))
				{
					if (game->config.so_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture SO déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
					game->config.so_textures = ft_strdup(trimmed);
					if (game->config.so_textures == NULL)
					{
						ft_putstr_fd("Error\nTexture SO déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(clean_line, "WE ", 3))
				{
					if (game->config.we_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture WE déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
					game->config.we_textures = ft_strdup(trimmed);
					if (game->config.we_textures == NULL)
					{
						ft_putstr_fd("Error\nTexture WE déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(clean_line, "EA ", 3))
				{
					if (game->config.ea_textures != NULL)
					{
						ft_putstr_fd("Error\nTexture EA déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
					game->config.ea_textures = ft_strdup(trimmed);
					if (game->config.ea_textures == NULL)
					{
						ft_putstr_fd("Error\nTexture EA déjà définie.\n", 2);
						free(clean_line);
						exit(EXIT_FAILURE);
					}
				}
				printf("Chemin texture: %s\n", trimmed);
				free(trimmed);
			}
			else if (!ft_strncmp(clean_line, "F ", 2) ||
					 !ft_strncmp(clean_line, "C ", 2))
			{
				trimmed = ft_strtrim(clean_line + 2, " \t\n");
				if (!trimmed)
				{
					ft_putstr_fd("Error\nÉchec de l'allocation mémoire pour couleur.\n", 2);
					free(clean_line);
					close(fd);
					exit(EXIT_FAILURE);
				}
				parse_color(game, clean_line, trimmed);
				printf("Couleur lue: %s\n", trimmed);
				free(trimmed);
			}
			else
				append_map_line(game, ft_strdup(clean_line));
		}
		free(clean_line);
	}
	close(fd);
	return (0);
}
