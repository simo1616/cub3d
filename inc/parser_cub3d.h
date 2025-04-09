#ifndef PARSER_CUB3D_H
# define PARSER_CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

/* ===================== CONSTANTES ERREURS ===================== */

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
# define ERR_INVALID_COLOR_FORMAT "Error\nInvalid color format (need exactly 3 values)\n"
# define ERR_INVALID_COLOR_VALUE "Error\nCouleur invalide: \n"
# define ERR_UNKNOWN_COLOR_IDENTIFIER "Error\nIdentifiant de couleur inconnu \n"
# define ERR_MAP_FIRST_LAST_LINE "Error\nLigne (1ère/dernière) contient autre chose que '1'.\n"
# define ERR_MAP_START_LINE "Error\nUne ligne ne commence pas par un mur '1'.\n"
# define ERR_TEXTURE_NOT_DEFINED_NO "Error\nTexture NO non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_SO "Error\nTexture SO non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_WE "Error\nTexture WE non définie.\n"
# define ERR_TEXTURE_NOT_DEFINED_EA "Error\nTexture EA non définie.\n"
# define ERR_COLOR_NOT_DEFINED_F "Error\nCouleur F(Sol) non définie.\n"
# define ERR_COLOR_NOT_DEFINED_C "Error\nCouleur C(Plaf.) non définie.\n"
# define ERR_MAP_NOT_DEFINED "Error\nMap non définie.\n"
# define ERR_MAP_EMPTY "Error\nMap vide.\n"
# define ERR_MAP_INVALID_CHAR "Error\nCaractère invalide.\n"
# define ERR_MAP_TEXT_MORE_THAN_ONE "Error\nIl faut exactement 1 orientation (N,S,E,W).\n"
# define ERR_MAP_MALLOC "Error\nMalloc failed for visited.\n"
# define ERR_MAP_NOT_CLOSE "Error\nMap non fermée (fuite détectée)\n"
# define ERR_MAP_BAD "Error\nDes caractères trouvés après des lignes vides suivant la carte.\n"
# define ERR_MAP_POS "Error\nPosition de la map incorrecte (pas toutes les textures/couleurs lues).\n"
# define ERR_MAP_ADD "Error\nDes données supp après la carte.\n"

/* ===================== STRUCTURES ===================== */

typedef struct s_game t_game;
typedef struct s_config {
	char	*no_textures;
	char	*so_textures;
	char	*we_textures;
	char	*ea_textures;
	int		color_sol[3];
	int		color_plafond[3];
} t_config;

typedef enum e_parse_state {
	READING_CONFIG,
	READING_MAP,
	MAP_DONE
} t_parse_state;

typedef struct s_mapinfo {
	char	**map2d;
	bool	**visited;
	int		width;
	int		height;
} t_mapinfo;

typedef struct s_player_data {
	int		*count;
	int		*row;
	int		*col;
	t_mapinfo *info;
} t_player_data;

typedef struct s_cleanup_state {
	bool game_cleaned;
	bool parser_cleaned;
} t_cleanup_state;

typedef struct s_parser {
	int				fd;
	char			*line;
	char			*clean_line;
	char			*trimmed;
	int				match_text;
	int				match_color;
	bool			map_started;
	bool			map_is_done;
	bool			empty_line_after_map;
	t_game			*game;
	t_cleanup_state	*state;
} t_parser;

typedef struct s_line_info {
	int row;
	int first;
	int last;
} t_line_info;

/* ===================== FONCTIONS PRINCIPALES ===================== */

int				close_window(t_game *game);
int				key_press(int keycode, t_game *game);
void			init_config_game(t_game *game);
int				ft_parse(t_game *game, char *filename);

/* ===================== FONCTIONS DE PARSING ===================== */

void			parse_color(t_game *game, char *clean_line, char *color_str, t_parser *parser);
void			ft_split_three(t_game *game, char *clean_line, char *trimed);
void			append_map_line(t_game *game, char *clean_line);
void			check_validate_map(t_game *game, t_parser *parser);
void			free_split(char **tokens);
int				is_integer(char *str);
void			error_and_exit(char *msg);
void			error_and_exit_free(char **tokens, char *msg);
void			check_color_value(int value, t_parser *parser);
void			check_access(t_parser *parser);
void			final_check_config(t_game *game);

/* ===================== UTILITAIRES DE PARSING ===================== */

void			init_parser(t_parser *parser, t_game *game);
int				open_map_file(char *file_name);
void			process_texture_line(t_game *game, t_parser *parser);
void			process_color_line(t_game *game, t_parser *parser);
void			process_map_line(t_game *game, t_parser *parser);
void			handle_empty_line(t_parser *parser);
void			check_map_errors(t_parser *parser);
void			assign_texture(t_game *game, t_parser *parser);
void			assign_if_not_defined(char **texture_field, char *trimmed, char *error_msg, t_parser *parser);
bool			is_only_spaces(char *line);
void			check_first_or_last_line(char *line, t_parser *parser);
void			check_middle_line(char *line, int row, t_parser *parser);
void			check_line_borders(char *line, t_line_info info, t_parser *parser);
bool			dfs_closed(t_mapinfo *info, int r, int c);
bool			is_valid_map_char(char c);
void			exit_text_with_error(char *msg, t_parser *parser);

/* ===================== GESTION DE MAP ===================== */

void			init_visited_map(t_mapinfo *info);
void			free_mapinfo(t_mapinfo *info);
int				get_map_height(char **map);
void			check_map_empty(int height);
int				get_max_width(char **map, int height);
void			init_mapinfo_struct(t_mapinfo *info, char **map, int h, int w);
void			copy_and_pad_line(char *dest, char *src, int width);

/* ===================== CLEANUP ===================== */

void			free_map(char **map);
void			free_config(t_config *config);
void			cleanup_all(t_game *game, t_parser *parser);
void			cleanup_before_exit(t_game *game);
void			cleanup_parser_resources(t_parser *parser);
void			cleanup_get_next_line(void);

#endif