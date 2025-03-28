#ifndef CUB3D
# define CUB3D


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>



typedef struct s_config
{
	char		*no_textures;
	char		*so_textures;
	char		*we_textures;
	char		*ea_textures;
	int			color_sol[3];
	int			color_plafond[3];
} t_config;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_config	config;
} t_game;

int				close_window(t_game *game);
int				key_press(int keycode, t_game *game);
void 			init_config_game(t_game *game);
int				ft_parse(t_game *game ,char *file_name);
void 			ft_split_three(t_game *game, char *clean_line, char *trimed);
void 			append_map_line(t_game *game, char *clean_line);
void			free_split(char **tokens)






#endif