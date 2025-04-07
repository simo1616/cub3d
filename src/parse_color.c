#include "cub3d.h"

void	parse_color(t_game *game, char *clean_line, char *color_str)
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
			error_and_exit_free(tokens, "Error\nFormat de couleur invalide\n");
		i++;
	}
	i = 0;
	if (!ft_strncmp(clean_line, "F ", 2))
	{
		if (game->config.color_sol[0] != -1)
		{
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