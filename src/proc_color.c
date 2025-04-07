#include "cub3d.h"

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
