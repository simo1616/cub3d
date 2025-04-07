#include "cub3d.h"
 
void	init_parser(t_parser *parser)
{
	parser->match_text = 0;
	parser->match_color = 0;
	parser->map_started = false;
	parser->map_is_done = false;
	parser->empty_line_after_map = false;
	parser->line = NULL;
	parser->clean_line = NULL;
	parser->trimmed = NULL;
}

int	open_map_file(char *file_name)
{
	int fd;
	
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(ERR_OPEN_FILE, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

void	process_color_line(t_game *game, t_parser *parser)
{
	parser->match_color = 1;
	if (parser->clean_line[0] == 'F')
		parser->trimmed = ft_strtrim(parser->clean_line + 2, " \t\n");
	else if (parser->clean_line[0] == 'C')
		parser->trimmed = ft_strtrim(parser->clean_line + 2, " \t\n");
	
	if (!parser->trimmed)
	{
		ft_putstr_fd(ERR_MEM_ALLOC_COLOR, 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
	parse_color(game, parser->clean_line, parser->trimmed);
	printf("Couleur lue: %s\n", parser->trimmed);
	free(parser->trimmed);
}

void process_map_line(t_game *game, t_parser *parser)
{
	if (ft_strlen(parser->clean_line) == 0)
	{
		handle_empty_line(parser);
		return;
	}
	check_map_errors(parser);
	parser->map_started = true;
	append_map_line(game, ft_strtrim(parser->line, "\n"));
}

/* Gère une ligne vide */
void handle_empty_line(t_parser *parser)
{
	if (parser->map_started)
	{
		parser->map_is_done = true;
		parser->empty_line_after_map = true;
	}
}

void check_map_errors(t_parser *parser)
{
	if (parser->map_is_done)
	{
		ft_putstr_fd("Error\nDes données supp après la carte.\n", 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
	
	if (parser->empty_line_after_map)
	{
		ft_putstr_fd("Error\nDes caractères trouvés après des lignes vides suivant la carte.\n", 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
	
	if (!parser->match_text || !parser->match_color)
	{
		ft_putstr_fd("Error\nPosition de la map incorrecte (pas toutes les textures/couleurs lues).\n", 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
}

void cleanup_parser_resources(t_parser *parser, int fd)
{
	if (parser->clean_line)
		free(parser->clean_line);
	if (parser->line)
		free(parser->line);
	close(fd);
}


void process_line(t_game *game, t_parser *parser)
{
	if (!parser->clean_line || ft_strlen(parser->clean_line) == 0)
	{
		handle_empty_line(parser);
		return;
	}
	if (ft_strlen(parser->clean_line) > 0 && 
		(!ft_strncmp(parser->clean_line, "NO ", 3) || 
		!ft_strncmp(parser->clean_line, "SO ", 3) ||
		!ft_strncmp(parser->clean_line, "WE ", 3) || 
		!ft_strncmp(parser->clean_line, "EA ", 3)))
	{
		process_texture_line(game, parser);
	}
	else if (ft_strlen(parser->clean_line) > 0 && 
			(!ft_strncmp(parser->clean_line, "F ", 2) ||
			!ft_strncmp(parser->clean_line, "C ", 2)))
	{
		process_color_line(game, parser);
	}
	else
		process_map_line(game, parser);
}

int ft_parse(t_game *game, char *file_name)
{
	t_parser	parser;
	int			fd;
	
	init_parser(&parser);
	game->map = NULL;
	
	fd = open_map_file(file_name);
	if (fd == -1)
		return (1);
	while ((parser.line = get_next_line(fd)) != NULL)
	{
		parser.clean_line = ft_strtrim(parser.line, " \t\n");
		process_line(game, &parser);
		if (parser.clean_line)
		{
			free(parser.clean_line);
			parser.clean_line = NULL;
		}
		free(parser.line);
		parser.line = NULL;
	}
	check_validate_map(game);
	final_check_config(game);
	close(fd);
	return (0);
}
