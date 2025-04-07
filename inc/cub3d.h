#ifndef CUB3D
# define CUB3D


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

# define ERR_OPEN_FILE "Error\nImpossible d'ouvrir le fichier: "
# define ERR_MEM_ALLOC_TEXTURE "Error\nÉchec de l'allocation mémoire pour textures.\n"
# define ERR_EMPTY_TEXTURE_PATH "Error\nChemin de texture vide.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_NO "Error\nTexture NO déjà définie.\n"
# define ERR_MEM_ALLOC_TEXTURE_NO "Error\nÉchec de l'allocation mémoire pour texture NO.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_SO "Error\nTexture SO déjà définie.\n"
# define ERR_MEM_ALLOC_TEXTURE_SO "Error\nÉchec de l'allocation mémoire pour texture SO.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_WE "Error\nTexture WE déjà définie.\n"
# define ERR_MEM_ALLOC_TEXTURE_WE "Error\nÉchec de l'allocation mémoire pour texture WE.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_EA "Error\nTexture EA déjà définie.\n"
# define ERR_MEM_ALLOC_TEXTURE_EA "Error\nÉchec de l'allocation mémoire pour texture EA.\n"
# define ERR_MEM_ALLOC_COLOR "Error\nÉchec de l'allocation mémoire pour couleur.\n"
# define ERR_INVALID_COLOR_FORMAT "Error: Invalid color format (need exactly 3 values)\n"
# define ERR_INVALID_COLOR_VALUE "Couleur invalide: %d\n"
# define ERR_UNKNOWN_COLOR_IDENTIFIER "Identifiant de couleur inconnu \n"

typedef struct s_config
{
	char		*no_textures;
	char		*so_textures;
	char		*we_textures;
	char		*ea_textures;
	int			color_sol[3];
	int			color_plafond[3];
} t_config;

typedef struct s_mapinfo
{
    char  **map2d;
    bool  **visited;
    int    width;
    int    height;
}   t_mapinfo;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_config	config;
} t_game;

typedef enum e_parse_state {
    READING_CONFIG,
    READING_MAP,
    MAP_DONE
}   t_parse_state;

int				close_window(t_game *game);
int				key_press(int keycode, t_game *game);
void 			init_config_game(t_game *game);
int				ft_parse(t_game *game ,char *filename);
void 			ft_split_three(t_game *game, char *clean_line, char *trimed);
void 			append_map_line(t_game *game, char *clean_line);
void			check_validate_map(t_game *game);
void			free_split(char **tokens);
int				is_integer(char *str);
void			error_and_exit(char *msg);
void			error_and_exit_free(char **tokens, char *msg);
void			check_color_value(int value);
void 			check_access(char *trimmed, char *clean_line);
void 			final_check_config(t_game *game);






#endif