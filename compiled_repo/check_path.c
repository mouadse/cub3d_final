/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:26:42 by msennane          #+#    #+#             */
/*   Updated: 2025/06/04 16:06:32 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_colors_loaded_count(t_cub3d *game, t_config *config,
				const char *original_line, const char *trimmed_line_start);

void	check_spaces_after_identifier(t_cub3d *game, char *line_content_start,
		const char *identifier, char *original_line)
{
	size_t	identifier_len;
		char error_msg[100] = "Error: Missing space after identifier '";

	identifier_len = ft_strlen(identifier);
	if (ft_strncmp(identifier, line_content_start, identifier_len) == 0
		&& ft_isspace(line_content_start[identifier_len]))
	{
		return ;
	}
	else
	{
		free(original_line);
		ft_strlcat(error_msg, identifier, sizeof(error_msg));
		ft_strlcat(error_msg, "'.\n", sizeof(error_msg));
		handle_error(error_msg, game);
	}
}

void	trim_trailing_whitespace_or_newline(t_cub3d *game, char *str,
		char *original_line)
{
	size_t	i;
	size_t	path_len;

	path_len = 0;
	while (str[path_len] && !ft_isspace(str[path_len]))
		path_len++;
	i = path_len;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isspace(str[i]))
		{
			free(original_line);
			handle_error("Error: Invalid characters found after texture path.\n", game);
		}
		i++;
	}
	str[path_len] = '\0';
}

static void	validate_texture_preconditions(t_cub3d *game,
		const t_texture_args *args)
{
	if (*(args->target_texture_path_ptr) != NULL)
	{
		free(args->original_line);
		handle_error("Error: Duplicate texture path definition.\n", game);
	}
	check_spaces_after_identifier(game, args->line_content_start,
		args->identifier, args->original_line);
}

static char	*skip_identifier_and_spaces(const t_texture_args *args,
		int *identifier_occurrences)
{
	char	*path_start;

	path_start = args->line_content_start;
	*identifier_occurrences = 0;
	while (*path_start && (ft_isspace(*path_start)
			|| (path_start == args->line_content_start
				&& ft_strncmp(args->identifier, path_start,
					ft_strlen(args->identifier)) == 0)))
	{
		if (path_start == args->line_content_start
			&& ft_strncmp(args->identifier, path_start,
				ft_strlen(args->identifier)) == 0)
		{
			(*identifier_occurrences)++;
			path_start += ft_strlen(args->identifier);
		}
		else if (ft_isspace(*path_start))
			path_start++;
		else
			break ;
	}
	return (path_start);
}

static char	*extract_and_validate_path_segment(t_cub3d *game,
		const t_texture_args *args)
{
	char	*path_start;
	int		identifier_occurrences;

	path_start = skip_identifier_and_spaces(args, &identifier_occurrences);
	trim_trailing_whitespace_or_newline(game, path_start, args->original_line);
	if (!check_path(path_start) || identifier_occurrences != 1)
	{
		free(args->original_line);
		handle_error("Error: Invalid texture file path or malformed texture line.\n", game);
		return (NULL);
	}
	return (path_start);
}

static void	handle_texture_path_line(t_cub3d *game, t_texture_args *args,
		bool *processed_successfully)
{
	if (ft_strncmp("NO", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->no_texture_path);
		args->identifier = "NO";
	}
	else if (ft_strncmp("SO", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->so_texture_path);
		args->identifier = "SO";
	}
	else if (ft_strncmp("WE", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->we_texture_path);
		args->identifier = "WE";
	}
	else if (ft_strncmp("EA", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->ea_texture_path);
		args->identifier = "EA";
	}
	else
		return ;
	copy_texture_path(game, args, processed_successfully);
}

static void	handle_rgb_line(t_cub3d *game, t_rgb_params *params)
{
	check_rgb(game, params);
}

static bool	process_texture_identifiers(t_cub3d *game, char *trimmed_line_start,
				char *original_line, bool *processed_successfully)
{
	t_texture_args	args;

	if (ft_strncmp("NO", trimmed_line_start, 2) == 0
		|| ft_strncmp("SO", trimmed_line_start, 2) == 0
		|| ft_strncmp("WE", trimmed_line_start, 2) == 0
		|| ft_strncmp("EA", trimmed_line_start, 2) == 0)
	{
		args.line_content_start = trimmed_line_start;
		args.original_line = original_line;
		handle_texture_path_line(game, &args, processed_successfully);
		return (true);
	}
	return (false);
}

static bool	process_color_identifiers(t_cub3d *game, char *trimmed_line_start,
				char *original_line, bool *processed_successfully)
{
	t_rgb_params	rgb_params;

	if (ft_strncmp("F", trimmed_line_start, 1) == 0)
	{
		rgb_params.target_color_value = &game->config->floor_rgb;
		rgb_params.line_content_start = trimmed_line_start;
		rgb_params.original_line = original_line;
		rgb_params.identifier_char = 'F';
		rgb_params.processed_flag = processed_successfully;
		handle_rgb_line(game, &rgb_params);
		return (true);
	}
	else if (ft_strncmp("C", trimmed_line_start, 1) == 0)
	{
		rgb_params.target_color_value = &game->config->ceiling_rgb;
		rgb_params.line_content_start = trimmed_line_start;
		rgb_params.original_line = original_line;
		rgb_params.identifier_char = 'C';
		rgb_params.processed_flag = processed_successfully;
		handle_rgb_line(game, &rgb_params);
		return (true);
	}
	return (false);
}

static bool	process_texture_line(t_cub3d *game, char *trimmed_line_start,
				char *original_line, bool *processed_successfully)
{
	if (process_texture_identifiers(game, trimmed_line_start,
			original_line, processed_successfully))
		return (true);
	if (process_color_identifiers(game, trimmed_line_start,
			original_line, processed_successfully))
		return (true);
	return (false);
}

void	parse_texture_file_path(t_cub3d *game, t_config *config,
		char *trimmed_line_start, char *original_line)
{
	bool	processed_successfully;
	bool	identifier_found;

	(void)config;
	processed_successfully = false;
	identifier_found = process_texture_line(game, trimmed_line_start,
			original_line, &processed_successfully);
	if (identifier_found)
	{
		if (processed_successfully)
		{
			game->config->loaded_textures++;
			check_colors_loaded_count(game, game->config, original_line,
				trimmed_line_start);
		}
	}
	else
	{
		if (trimmed_line_start[0] != '\n' && trimmed_line_start[0] != '\0')
		{
			free(original_line);
			handle_error("Error: Invalid identifier or line format in map file configuration section.\n", game);
		}
	}
}

static void	check_colors_loaded_count(t_cub3d *game, t_config *config,
		const char *original_line, const char *trimmed_line_start)
{
	static int	ceiling_definitions = 0;
	static int	floor_definitions = 0;

	if (ft_strncmp("F", trimmed_line_start, 1) == 0)
		floor_definitions++;
	if (ft_strncmp("C", trimmed_line_start, 1) == 0)
		ceiling_definitions++;
	if (ceiling_definitions == 1 && floor_definitions == 1)
		config->textures_ready = true;
	if (ceiling_definitions > 1 || floor_definitions > 1)
	{
		free((void *)original_line);
		handle_error("Error: Duplicate color definition (Floor or Ceiling).\n", game);
	}
}

void	copy_texture_path(t_cub3d *game, const t_texture_args *args,
		bool *processed_flag)
{
	char	*valid_path_segment;

	validate_texture_preconditions(game, args);
	valid_path_segment = extract_and_validate_path_segment(game, args);
	*(args->target_texture_path_ptr) = ft_strdup(valid_path_segment);
	if (!*(args->target_texture_path_ptr))
	{
		free(args->original_line);
		handle_error("Error: Memory allocation failed for texture path (ft_strdup).\n", game);
	}
	*processed_flag = true;
}
