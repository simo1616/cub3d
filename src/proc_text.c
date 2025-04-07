#include "cub3d.h"

static void	trim_texture_path(t_parser *parser)
{
	if (parser->clean_line[0] == 'N' && parser->clean_line[1] == 'O')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
	else if (parser->clean_line[0] == 'S' && parser->clean_line[1] == 'O')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
	else if (parser->clean_line[0] == 'W' && parser->clean_line[1] == 'E')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
	else if (parser->clean_line[0] == 'E' && parser->clean_line[1] == 'A')
		parser->trimmed = ft_strtrim(parser->clean_line + 3, " \t\n");
}

static void	check_trimmed_not_null(t_parser *parser)
{
	if (parser->trimmed == NULL)
	{
		ft_putstr_fd(ERR_MEM_ALLOC_TEXTURE, 2);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
}

static void	check_trimmed_not_empty(t_parser *parser)
{
	if (ft_strlen(parser->trimmed) == 0)
	{
		ft_putstr_fd(ERR_EMPTY_TEXTURE_PATH, 2);
		free(parser->trimmed);
		free(parser->clean_line);
		free(parser->line);
		exit(EXIT_FAILURE);
	}
}

void	process_texture_line(t_game *game, t_parser *parser)
{
	parser->match_text = 1;
	trim_texture_path(parser);
	check_trimmed_not_null(parser);
	check_trimmed_not_empty(parser);
	check_access(parser->trimmed, parser->clean_line);
	assign_texture(game, parser);
	printf("Chemin texture: %s\n", parser->trimmed);
	free(parser->trimmed);
}


