/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbendidi <mbendidi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:33:09 by mbendidi          #+#    #+#             */
/*   Updated: 2025/06/23 21:34:29 by mbendidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CUB3D_H
# define PARSER_CUB3D_H

# include "parser_errors.h"
# include <fcntl.h>
# include <libft.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ===================== STRUCTURES ===================== */

struct					s_parser;
typedef struct s_config	t_config;
typedef struct s_game	t_game;
typedef struct s_parser	t_parser;

typedef enum e_parse_state
{
	READING_CONFIG,
	READING_MAP,
	MAP_DONE
}						t_parse_state;

typedef struct s_mapinfo
{
	char				**map2d;
	bool				**visited;
	int					width;
	int					height;
}						t_mapinfo;

typedef struct s_player_data
{
	int					*count;
	int					*row;
	int					*col;
	t_mapinfo			*info;
	t_parser			*parser;
}						t_player_data;

typedef struct s_cleanup_state
{
	bool				game_cleaned;
	bool				parser_cleaned;
}						t_cleanup_state;

typedef struct s_parser
{
	int					fd;
	char				*line;
	char				*clean_line;
	char				*trimmed;
	int					match_text;
	int					match_color;
	bool				config_complete; // 
	bool				map_started;
	bool				map_is_done;
	bool				empty_line_after_map;
	t_game				*game;
	t_cleanup_state		*state;
}						t_parser;

typedef struct s_line_info
{
	int					row;
	int					first;
	int					last;
}						t_line_info;

/* ===================== FONCTIONS PRINCIPALES ===================== */

int						close_window(t_game *game);
void					init_structs(t_game *game);
int						ft_parse(t_game *game, char *filename);

/* ===================== FONCTIONS DE PARSING ===================== */

void					parse_color(t_game *game, char *clean_line,
							char *color_str, t_parser *parser);
void					ft_split_three(t_game *game, char *clean_line,
							char *trimed);
void					append_map_line(t_game *game, char *clean_line);
void					check_validate_map(t_game *game, t_parser *parser);
void					free_split(char **tokens);
int						is_integer(char *str);
void					error_exit_game(t_game *game, char *msg);
void					error_and_exit(t_parser *parser, char *msg);
void					error_and_exit_free(t_parser *parser, char **tokens,
							char *msg);
void					check_color_value(int value, t_parser *parser);
void					check_access(t_parser *parser);
void					final_check_config(t_game *game, t_parser *parser);

/* ===================== UTILITAIRES DE PARSING ===================== */

void					init_parser(t_parser *parser, t_game *game);
int						open_map_file(char *file_name);
void					process_texture_line(t_game *game, t_parser *parser);
void					process_color_line(t_game *game, t_parser *parser);
void					process_map_line(t_game *game, t_parser *parser);
void					handle_empty_line(t_parser *parser);
void					check_map_errors(t_parser *parser);
void					assign_texture(t_game *game, t_parser *parser);
void					assign_if_not_defined(char **texture_field,
							char *trimmed, char *error_msg, t_parser *parser);
bool					is_only_spaces(char *line);
void					check_first_or_last_line(char *line, t_parser *parser);
void					check_middle_line(char *line, int row,
							t_parser *parser);
void					check_line_borders(char *line, t_line_info info,
							t_parser *parser);
bool					dfs_closed(t_mapinfo *info, int r, int c);
bool					is_valid_map_char(char c);
void					exit_text_with_error(char *msg, t_parser *parser);

/* ===================== GESTION DE MAP ===================== */

void					init_visited_map(t_mapinfo *info, t_parser *parser);
void					free_mapinfo(t_mapinfo *info);
int						get_map_height(char **map);
void					check_map_empty(int height);
int						get_max_width(char **map, int height);
void					init_mapinfo_struct(t_mapinfo *info, t_game *game,
							t_parser *parser);
void					copy_and_pad_line(char *dest, char *src, int width);

/* ===================== VALIDATE LINE HELPERS ===================== */

bool					is_texture_attempt(char *line);
bool					is_valid_texture_format(char *line);
bool					is_color_attempt(char *line);
bool					is_valid_color_format(char *line);
bool					is_map_line(char *line);

/* ===================== CLEANUP ===================== */

void					free_map(char **map);
void					free_config(t_config *config);
void					cleanup_all(t_game *game, t_parser *parser);
void					cleanup_before_exit(t_game *game);
void					cleanup_parser_resources(t_parser *parser);
void					cleanup_get_next_line(void);

#endif