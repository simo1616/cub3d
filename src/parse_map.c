# include "cub3d.h"

static int check_first_line(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] != '1' && line[i] != ' ')
			return(0);
		i++;
	}
	return(1);
}

static int check_char(char c)
{
	return(c != ' ' && c != '0' && c != '1' &&
		c != 'N' && c != 'S' && c != 'E' && c != 'W');
}

static int check_line_map(char *line)
{
	int i;
	
	i = 0;
	while(line[i])
	{
		if(check_char(line[i]))
		{
			printf("\n***********\n\tERROOOOOOOOOOOR de map dans check LINe \n\n");
			return(0);
		}
		i++;
	}
	return(1);
}


void	check_validate_map(t_game *game)
{
	int i;

	i = 0;
	
	while(game->map[i])
	{
		//printf("verif de la map = %s\n", game->map[i]);
		if(!check_line_map(game->map[i]))
		{
			printf("\n***********\n\tERROOOOOOOOOOOR de map dans check map  \nici ===> %s\n", game->map[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	
}

void check_valid_first_last_line(t_game *game, int i)
{
	if(game->map[i])
	{
		if(!check_first_line(game->map[i]))
		{
			printf("\n***********\n\tERROOOOOOOOOOOR de map dans la 1er ligne \nici ===> %s\n", game->map[i]);
			exit(EXIT_FAILURE);
		}
	}
}


void	append_map_line(t_game *game, char *cpy_line)
{
	int		i;
	int		cnt;
	char	**new_map;

	cnt = 0;
	if(game->map)
	{
		while(game->map[cnt])
			cnt++;
	}
	new_map = (char **)malloc(sizeof(char *) * (cnt + 2));
	if (!new_map)
	{
		perror("Erreur d'allocation pour la map.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	if(game->map)
	{
		while(game->map[i])
		{
			new_map[i] = game->map[i];
			i++;
		}
	}
	new_map[i] = cpy_line;
	new_map[i + 1] = NULL;
	if(game->map)
		free(game->map);
	game->map = new_map;
}
