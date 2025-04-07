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
# define ERR_TEXTURE_ALREADY_DEFINED_SO "Error\nTexture SO déjà définie.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_WE "Error\nTexture WE déjà définie.\n"
# define ERR_TEXTURE_ALREADY_DEFINED_EA "Error\nTexture EA déjà définie.\n"
# define ERR_MEM_ALLOC_TEXTURE_NO "Error\nÉchec de l'allocation mémoire pour texture NO.\n"
# define ERR_MEM_ALLOC_TEXTURE_SO "Error\nÉchec de l'allocation mémoire pour texture SO.\n"
# define ERR_MEM_ALLOC_TEXTURE_WE "Error\nÉchec de l'allocation mémoire pour texture WE.\n"
# define ERR_MEM_ALLOC_TEXTURE_EA "Error\nÉchec de l'allocation mémoire pour texture EA.\n"
# define ERR_MEM_ALLOC_COLOR "Error\nÉchec de l'allocation mémoire pour couleur.\n"
# define ERR_INVALID_COLOR_FORMAT "Error\n Invalid color format (need exactly 3 values)\n"
# define ERR_INVALID_COLOR_VALUE "Error\nCouleur invalide: \n"
# define ERR_UNKNOWN_COLOR_IDENTIFIER "Error\nIdentifiant de couleur inconnu \n"
# define ERR_MAP_FIRST_LAST_LINE "Error\nLigne (1ère/dernière) contient autre chose que '1'.\n"
# define ERR_MAP_START_LINE "Error\nUne ligne ne commence pas par un mur '1'.\n"
# define ERR_TEXTURE_NOT_DEFINED_NO "Error\nTexture NO non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_SO "Error\nTexture SO non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_WE "Error\nTexture WE non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_EA "Error\nTexture EA non définie.\n"
# define ERR_COLOR_NOT_DEFINED_F "Error\nColeur F(Sol) non définie.\n"
# define ERR_COLOR_NOT_DEFINED_C "Error\nColeur C(Plaf.) non définie.\n"
# define ERR_MAP_NOT_DEFINED "Error\nmap non définie.\n"
# define ERR_MAP_EMPTY "Error\nMap vide.\n"
# define ERR_MAP_INVALID_CHAR "Error\nCaractère invalide.\n"
# define ERR_MAP_TEXT_MORE_THAN_ONE "Error\nIl faut exactement 1 orientation (N,S,E,W).\n"
# define ERR_MAP_MALLOC "Error\nMalloc failed for visited.\n"
# define ERR_MAP_NOT_CLOSE "Error\nMap non fermée (fuite détectée)\n"

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

/* Structure pour regrouper les variables de parsing */
typedef struct s_parser
{
    int         fd;
    char        *line;
    char        *clean_line;
    char        *trimmed;
    int         match_text;
    int         match_color;
    bool        map_started;
    bool        map_is_done;
    bool        empty_line_after_map;
} t_parser;

int				close_window(t_game *game);
int				key_press(int keycode, t_game *game);
void 			init_config_game(t_game *game);
int				ft_parse(t_game *game ,char *filename);
void			parse_color(t_game *game, char *clean_line, char *color_str);
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


/* Fonctions de parsing */
void    init_parser(t_parser *parser);
int     open_map_file(char *file_name);
void    process_texture_line(t_game *game, t_parser *parser);
void    process_color_line(t_game *game, t_parser *parser);
void    process_map_line(t_game *game, t_parser *parser);
void    handle_empty_line(t_parser *parser);
void    check_map_errors(t_parser *parser);
void    cleanup_parser_resources(t_parser *parser, int fd);
void	assign_texture(t_game *game, t_parser *parser);

bool	is_only_spaces(char *line);
void	check_first_or_last_line(char *line);
void	check_middle_line(char *line, int row);
void	check_line_borders( char *line, int row, int first, int last);
bool	dfs_closed(t_mapinfo *info, int r, int c);
bool	is_valid_map_char(char c);

void	init_visited_map(t_mapinfo *info);
void	free_mapinfo(t_mapinfo *info);
int	get_map_height(char **map);
void	check_map_empty(int height);
int	get_max_width(char **map, int height);

void	init_mapinfo_struct(t_mapinfo *info, char **map, int h, int w);
void	copy_and_pad_line(char *dest, char *src, int width);




#endif