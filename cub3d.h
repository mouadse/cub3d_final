/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:43:24 by msennane          #+#    #+#             */
/*   Updated: 2025/04/10 12:31:20 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ERR_MISSING_MAP "Error: no map file.\n"
# define ERR_TOO_MANY_ARGS "Error: too many args.\n"
# define ERR_INVALID_EXTENSION "Error: invalid .cub file.\n"
# define ERR_INVALID_CHARACTER "Error: bad character in map.\n"
# define ERR_PLAYER_COUNT "Error: one player required.\n"

typedef struct s_validator
{
	int			invalid_char_count;
	int			player_count;
}				t_validator;

typedef struct s_config
{
	char		**grid;
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	uint32_t	floor_rgb;
	uint32_t	ceiling_rgb;
	bool		textures_ready;
	int			loaded_textures;
	int			grid_rows;
	int			grid_cols;
	char		character_orientation;
	int			character_pos_x;
	int			character_pos_y;
}				t_config;

typedef struct s_cub3d
{
	t_config	*config;
}				t_cub3d;

/* File handling and validation */
void			validate_map(int argc, char **argv, t_cub3d *game);
void			check_arguments(int argc);
void			check_extension(char *map_file);
int				check_path(char *path);
int				open_file(char *map_file);

/* Data processing */
void			data_processing(char *map_file, t_config *config);
void			read_textures_path(t_config *config, char *temp, int fd);
void			read_textures_path_aux(t_config *config, char *temp,
					char *line);

/* Texture path processing */
void			copy_texture_path(char **texture, char *path, char *mode,
					char *line);
void			trim_newline(char *str, char *line);
void			check_spaces(char *temp, char *mode, char *line);

/* RGB color processing */
void			check_rgb(uint32_t *color, char *rgb_color, char *original,
					char c);
void			split_rgb(char ***rgb, char *rgb_color, char *original, char c);
uint32_t		convert_rgb(int r, int g, int b);

/* Wall validation */
bool			check_diagonals(t_config *config, int line, int col);
bool			check_sides(t_config *config, int line, int col);
void			surrounded_by_walls(t_config *config);

/* Map processing */
void			count_map_size(t_config *config, char *temp, int fd);
void			read_and_copy_map_content(char *temp, int fd);
void			analyze_map_content(t_config *config, t_validator *validator);

/* Map utility functions */
void			get_max_lines(t_config *config);
void			get_max_columns(t_config *config);
void			check_map_content(t_validator *validator);
int				check_invalid_char(char c);

/* Tab handling */
int				count_tabs(char *line);
void			found_tabs(t_config *config);
char			*replace_tabs(char *line, int tabs);

/* Memory and error handling */
void			free_memory(t_cub3d *game);
t_cub3d			*get_game(t_cub3d *game);
void			handle_error(char *message);
void			init_variables_valid(t_validator *validator);

/* File reading utilities */
char			*get_next_line(int fd);
void			ft_free_matrix(char **matrix);

/* String utilities */

int				ft_isspace(int c);

#endif
