/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:43:24 by msennane          #+#    #+#             */
/*   Updated: 2025/05/06 14:44:43 by msennane         ###   ########.fr       */
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

# define PI 3.141592653589793
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

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

typedef struct s_cub3d
{
	void *mlx_ptr;          // MLX library context
	void *window_ptr;       // MLX window/image pointer
	void *north_texture;    // North wall texture
	void *south_texture;    // South wall texture
	void *west_texture;     // West wall texture
	void *east_texture;     // East wall texture
	int *texture_pixels[4]; // Texture pixel buffers (N, S, W, E)
	t_vec2 player_pos;      // Player position
	t_vec2 player_dir;      // Player direction
	t_vec2 camera_plane;    // Camera plane for raycasting
	int last_hit_side;      // Last wall side hit (0: X, 1: Y)
	float frame_time;       // Time per frame
	t_config *config;       // Game configuration
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

/* Matrix and Vector Operations */

t_vec2			create_vector(float x, float y);
t_vec2			vector_add(t_vec2 a, t_vec2 b);
t_vec2			vector_subtract(t_vec2 a, t_vec2 b);
t_vec2			vector_multiply(t_vec2 a, float scalar);
float			vector_magnitude(t_vec2 a);
t_vec2			rotate_vector(t_vec2 vector, float angle);

/* Raycasting math utilities */
int				sign_of(float v);
t_vec2			calc_delta_dist(t_vec2 dir);
void			init_side_dist(t_dda *ray, t_vec2 pos);

/* Raycasting core functions */
void			perform_dda(t_dda *ray, char **map, int *hit_side);
void			draw_rays(t_cub3d *game);

#endif
