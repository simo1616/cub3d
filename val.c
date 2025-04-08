char	*ft_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!str)
	{
		free(left_str);
		return (NULL);
	}
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}


char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	return (line);
}

static void	parse_loop(t_game *game, t_parser *parser, int fd)
{
	parser->line = get_next_line(fd);
	while (parser->line)
	{
		parser->clean_line = ft_strtrim(parser->line, " \t\n");
		process_line(game, parser);
		if (parser->clean_line)
		{
			free(parser->clean_line);
			parser->clean_line = NULL;
		}
		free(parser->line);
		parser->line = NULL;
		parser->line = get_next_line(fd);
	}
	cleanup_get_next_line();
}

int	ft_parse(t_game *game, char *file_name)
{
	t_parser	parser;
	int			fd;

	init_parser(&parser, game);
	game->map = NULL;
	fd = open_map_file(file_name);
	if (fd == -1)
		return (EXIT_FAILURE);
	parse_loop(game, &parser, fd);
	check_validate_map(game, &parser);
	final_check_config(game);
	close(fd);
	return (EXIT_SUCCESS);
}


int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Usage: ./cub3d map.cub\n");
		return (EXIT_FAILURE);
	}
	init_config_game(&game);
	if (ft_parse(&game, av[1]))
		return (1);
	//print_debug(&game);
	// game.mlx = mlx_init();
	// if (!game.mlx)
	// {
	// 	printf("Erreur : Init mlx\n");
	// 	return (1);
	// }
	// game.win = mlx_new_window(game.mlx, 800, 600, "Cube3D");
	// if (!game.win)
	// {
	// 	printf("Erreur : new_window\n");
	// 	mlx_destroy_display(game.mlx);
	// 	free(game.mlx);
	// 	return (1);
	// }
	// mlx_hook(game.win, 17, 0, close_window, &game);
	// mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	// mlx_loop(game.mlx);
	cleanup_before_exit(&game);
	cleanup_get_next_line();
	return (0);
}
