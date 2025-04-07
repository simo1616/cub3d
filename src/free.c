# include "cub3d.h"

void	free_split(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void cleanup_parser_resources(t_parser *parser, int fd)
{
	if (parser->clean_line)
		free(parser->clean_line);
	if (parser->line)
		free(parser->line);
	close(fd);
}