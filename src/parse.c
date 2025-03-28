#include "cub3d.h"

static void	check_valid_color_value(int val, char *color_str)
{
	if (val < 0 || val > 255)
	{
		// utiliser strerror
		perror("Error: Color value out of range [0-255]\n");
		exit(EXIT_FAILURE);
	}
}


static void	parse_color(t_game *game, char *clean_line, char *color_str)
{
	char	**tokens;
	int		tok_cnt;
	int		i;

	tokens = ft_split(color_str, ',');
	if (!tokens)
	{
		perror("Erreur: ft_split a échoué\n");
		exit(EXIT_FAILURE);
	}
	tok_cnt = 0;
	while(tokens[tok_cnt])
		tok_cnt++;
	if(tok_cnt != 3)
	{
		// utiliser strerror
		perror("Error: Invalid color format (need exactly 3 values)\n");
		free_split(tokens);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < 3)
	{
		if (!tokens[i])
		{
			perror("Format de couleur invalide\n");
			free_split(tokens);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	if (!ft_strncmp(clean_line, "F ", 2))
	{
		while (i < 3)
		{
			game->config.color_plafond[i] = ft_atoi(tokens[i]);
			if(game->config.color_plafond[i] < 0 || game->config.color_plafond[i] > 255)
			{
				perror("Couleur invalide: %d\n");
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
	else if (!ft_strncmp(clean_line, "C ", 2))
	{
		while (i < 3)
		{
			game->config.color_sol[i] = ft_atoi(tokens[i]);
			if(game->config.color_sol[i]  < 0 || game->config.color_sol[i] > 255)
			{
				fprintf(stderr, "Couleur invalide: %d\n", val);
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
	else
	{
		fprintf(stderr, "Identifiant de couleur inconnu: \"%s\"\n", clean_line);
		free_split(tokens);
		exit(EXIT_FAILURE);
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
		fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier %s\n", file_name);
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
				if (!ft_strncmp(clean_line, "NO ", 3))
					game->config.no_textures = ft_strdup(trimmed);
				else if (!ft_strncmp(clean_line, "SO ", 3))
					game->config.so_textures = ft_strdup(trimmed);
				else if (!ft_strncmp(clean_line, "WE ", 3))
					game->config.we_textures = ft_strdup(trimmed);
				else if (!ft_strncmp(clean_line, "EA ", 3))
					game->config.ea_textures = ft_strdup(trimmed);
				printf("Chemin texture: %s\n", trimmed);
				free(trimmed);
			}
			else if (!ft_strncmp(clean_line, "F ", 2) ||
					 !ft_strncmp(clean_line, "C ", 2))
			{
				trimmed = ft_strtrim(clean_line + 2, " \t\n");
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
