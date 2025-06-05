/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:43:24 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:24:41 by msennane         ###   ########.fr       */
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

# define ERR_MISSING_MAP "Error: missing map file\n"
# define ERR_TOO_MANY_ARGS "Error: too many arguments\n"
# define ERR_INVALID_EXTENSION "Error: invalid .cub file\n"
# define ERR_INVALID_CHARACTER "Error: invalid character in map\n"
# define ERR_PLAYER_COUNT "Error: exactly one player required\n"
# define MEM_ERR "Error: memory allocation failed replacing tabs\n"
# define ERR_MISSING_TEXTURES "Error: missing texture or color definitions\n"
# define MLX_ADDR_ERR "Error: mlx_get_data_addr failed on texture: "
# define LOAD_TEXTURES_ERR "Error: game, config, or MLX not initialized\n"
# define ERR_TRAILING_CHARS "Error: extra characters after texture path\n"
# define ERR_INVALID_TEXTURE_PATH "Error: invalid texture path\n"
# define ERR_DUPLICATE_TEXTURE_PATH "Error: duplicate texture path\n"
# define ERR_TEXTURE_ALLOC "Error: memory allocation failed for texture path\n"
# define ERR_INVALID_IDENTIFIER "Error: invalid identifier or format\n"
# define MAP_WALL_ERROR "Error: map not enclosed by walls\n"
# define ERR_NO_MAP_CONTENT "Error: no map content found\n"
# define ERR_MAP_AFTER_EMPTY "Error: map content after empty line\n"
# define ERR_NO_VALID_MAP "Error: no valid map after textures\n"
# define ERR_FT_STRTRIM_FAIL "Error: ft_strtrim allocation failed\n"
# define ERR_MAP_DIMENSIONS "Error: map dimensions exceed expected size\n"

# define PI 3.141592653589793
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define FIXED_FRAME_TIME 0.016f
# define MAP_STARTED 0
# define MAP_ENDED 1

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFTAR 65361
# define KEY_RIGHTAR 65363

typedef struct s_keys
{
	bool		w;
	bool		s;
	bool		a;
	bool		d;
	bool		left;
	bool		right;
}				t_keys;

typedef struct s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

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

typedef struct s_texture_args
{
	char		**target_texture_path_ptr;
	char		*line_content_start;
	const char	*identifier;
	char		*original_line;
}				t_texture_args;

typedef struct s_rgb_parse_args
{
	uint32_t	*target_color_value;
	char		*rgb_values_str;
	char		*original_line;
	char		identifier_char;
}				t_rgb_parse_args;

typedef struct s_rgb_params
{
	uint32_t	*target_color_value;
	char		*line_content_start;
	char		*original_line;
	char		identifier_char;
	bool		*processed_flag;
}				t_rgb_params;

typedef struct s_rgb_error_context
{
	char		*original_line;
	char		**all_components_array;
}				t_rgb_error_context;

typedef struct s_wall_slice
{
	int			slice_height;
	int			draw_start_y;
	int			draw_end_y;
	int			tex_x;
	int			tex_y;
	float		hit_pos_x;
	float		tex_step;
	float		tex_pos;
}				t_wall_slice;

typedef struct s_dda
{
	float		plane_multiplier;
	t_vec2		dir;
	t_vec2		camera_pixel;
	t_vec2		delta_dist;
	t_vec2		dist_side;
	t_point		map;
	t_point		step;
	int			hit_side;
	float		perp_dist;
	float		wall_hit_x;
}				t_dda;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_tex
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_tex;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_tex		*north_texture;
	t_tex		*south_texture;
	t_tex		*west_texture;
	t_tex		*east_texture;
	t_tex		*texture;
	int			*texture_pixels[4];
	t_vec2		player_pos;
	t_vec2		player_dir;
	t_vec2		camera_plane;
	int			last_hit_side;
	float		frame_time;
	t_keys		keys;
	t_img		img;
	t_config	*config;
	bool		exit_requested;
	float		lerp_factor;
}				t_cub3d;

void			validate_map(int argc, char **argv, t_cub3d *game);
void			check_arguments(t_cub3d *game, int argc);
void			check_extension(t_cub3d *game, char *map_file);
int				check_path(char *path);

int				open_file(char *map_file, t_cub3d *game);
bool			is_map_content_line(char *line);

void			process_map_file(t_cub3d *game, char *map_file);
void			read_textures_path(t_cub3d *game, int fd);
void			parse_texture_file_path(t_cub3d *game, t_config *config,
					char *trimmed_line_start, char *original_line);

void			copy_texture_path(t_cub3d *game, const t_texture_args *args,
					bool *processed_flag);
void			trim_newline(char *str, char *line);
void			check_spaces(char *temp, char *mode, char *line);
void			check_spaces_after_identifier(t_cub3d *game,
					char *line_content_start, const char *identifier,
					char *original_line);
void			trim_trailing_whitespace_or_newline(t_cub3d *game, char *str,
					char *original_line);
void			validate_texture_preconditions(t_cub3d *game,
					const t_texture_args *args);
char			*skip_identifier_and_spaces(const t_texture_args *args,
					int *identifier_occurrences);
char			*extract_and_validate_path_segment(t_cub3d *game,
					const t_texture_args *args);

void			check_rgb(t_cub3d *game, t_rgb_params *params);
void			split_rgb(char ***rgb, char *rgb_color, char *original, char c);
uint32_t		convert_rgb(int r, int g, int b);

bool			check_diagonals(t_config *config, int line, int col);
bool			check_sides(t_config *config, int line, int col);
void			surrounded_by_walls(t_cub3d *game, t_config *config);

void			count_map_size(t_cub3d *game, char *map_file_path);
void			read_and_copy_map_content(t_cub3d *game, int fd);
void			analyze_map_content(t_config *config, t_validator *validator);

void			get_max_lines(t_config *config);
void			get_max_columns(t_config *config);
void			get_max_columns_with_filepath(t_config *config, char *filepath);
void			check_map_content(t_cub3d *game, t_validator *validator);
int				check_invalid_char(char c);

int				count_tabs(char *line);
void			found_tabs(t_config *config);
char			*replace_tabs(char *line, int tabs);

void			free_memory(t_cub3d *game);
void			handle_error(char *message,
					t_cub3d *game) __attribute__((noreturn));
void			init_variables_valid(t_validator *validator);

char			*get_next_line(int fd);
void			cleanup_get_next_line(void);
void			ft_free_matrix(char **matrix);

int				ft_isspace(int c);

t_vec2			create_vector(float x, float y);
t_vec2			vector_add(t_vec2 a, t_vec2 b);
t_vec2			vector_subtract(t_vec2 a, t_vec2 b);
t_vec2			vector_multiply(t_vec2 a, float scalar);
float			vector_magnitude(t_vec2 a);
t_vec2			rotate_vector(t_vec2 vector, float angle);

int				sign_of(float v);
t_vec2			calc_delta_dist(t_vec2 dir);
void			init_side_dist(t_dda *ray, t_vec2 pos);

void			perform_dda(t_dda *ray, char **map, int *hit_side);
void			draw_rays(t_cub3d *game);
void			draw_wall(t_dda *ray, t_cub3d *game, int pixel);

void			update_player_movement(t_cub3d *game);

void			init_player_camera(t_cub3d *game);
void			set_player_position_and_plane(t_cub3d *game);

void			draw_background(t_cub3d *game);
void			draw_background2(t_cub3d *game);

uint32_t		tex_pixel(t_tex *t, int x, int y);
void			init_image(t_cub3d *g, int w, int h);
void			my_mlx_pixel_put(t_img *img, int x, int y, uint32_t col);
void			load_textures(t_cub3d *game);
t_tex			*init_texture_data(void);

int				close_window(t_cub3d *game);
int				game_loop(t_cub3d *game);
int				key_press(int keycode, t_cub3d *game);
int				key_release(int keycode, t_cub3d *game);

bool			process_color_identifiers(t_cub3d *game,
					char *trimmed_line_start, char *original_line,
					bool *processed_successfully);
void			check_colors_loaded_count(t_cub3d *game, t_config *config,
					const char *original_line, const char *trimmed_line_start);

void			handle_texture_path_line(t_cub3d *game, t_texture_args *args,
					bool *processed_successfully);
bool			process_texture_identifiers(t_cub3d *game,
					char *trimmed_line_start, char *original_line,
					bool *processed_successfully);
bool			process_texture_line(t_cub3d *game, char *trimmed_line_start,
					char *original_line, bool *processed_successfully);

void			rgb_parse_err(t_cub3d *game, const char *error_message,
					char *original_line_to_free, char **rgb_components_to_free);
void			trigger_rgb_format_error(t_cub3d *game, char *original_line,
					char identifier_char);
void			validate_rgb_identifier_format(t_cub3d *game,
					const char *line_content_start, char *original_line,
					char identifier_char);

#endif
