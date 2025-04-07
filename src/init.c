# include "cub3d.h"

void init_config_game(t_game *game)
{
	game->mlx = NULL;
    game->win = NULL;
    game->config.no_textures = NULL;
    game->config.so_textures = NULL;
    game->config.we_textures = NULL;
    game->config.ea_textures = NULL;
    game->config.color_sol[0] = -1;
    game->config.color_plafond[0] = -1;
	game->map = NULL;
}

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

