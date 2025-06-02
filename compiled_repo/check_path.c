/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:26:42 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:44:21 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_colors_loaded_count(t_config *config, const char *original_line, const char *trimmed_line_start);

void	parse_texture_file_path(t_config *config, char *trimmed_line_start, char *original_line)
{
	bool	processed_successfully;

	processed_successfully = false;
	if (ft_strncmp("NO", trimmed_line_start, 2) == 0)
		copy_texture_path(&(config->no_texture_path), trimmed_line_start, "NO", original_line, &processed_successfully);
	else if (ft_strncmp("SO", trimmed_line_start, 2) == 0)
		copy_texture_path(&(config->so_texture_path), trimmed_line_start, "SO", original_line, &processed_successfully);
	else if (ft_strncmp("WE", trimmed_line_start, 2) == 0)
		copy_texture_path(&(config->we_texture_path), trimmed_line_start, "WE", original_line, &processed_successfully);
	else if (ft_strncmp("EA", trimmed_line_start, 2) == 0)
		copy_texture_path(&(config->ea_texture_path), trimmed_line_start, "EA", original_line, &processed_successfully);
	else if (ft_strncmp("F", trimmed_line_start, 1) == 0)
		check_rgb(&config->floor_rgb, trimmed_line_start, original_line, 'F', &processed_successfully);
	else if (ft_strncmp("C", trimmed_line_start, 1) == 0)
		check_rgb(&config->ceiling_rgb, trimmed_line_start, original_line, 'C', &processed_successfully);
	else
	{
		if (trimmed_line_start[0] != '\n' && trimmed_line_start[0] != '\0')
		{
			free(original_line);
			handle_error("Error: Invalid identifier or line format in map file configuration section.\n");
		}
		return;
	}

	if (processed_successfully)
	{
		config->loaded_textures++;
		check_colors_loaded_count(config, original_line, trimmed_line_start);
	}
}

static void	check_colors_loaded_count(t_config *config, const char *original_line, const char *trimmed_line_start)
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
		handle_error("Error: Duplicate color definition (Floor or Ceiling).\n");
	}
}

void	copy_texture_path(char **target_texture_path_ptr, char *line_content_start, const char *identifier, char *original_line, bool *processed_flag)
{
	int		identifier_occurrences;
	char	*path_start;

	identifier_occurrences = 0;
	if (*target_texture_path_ptr != NULL)
	{
		free(original_line);
		handle_error("Error: Duplicate texture path definition.\n");
	}

	check_spaces_after_identifier(line_content_start, identifier, original_line);

	path_start = line_content_start;
	while (*path_start && (ft_isspace(*path_start) ||
		   (path_start == line_content_start && ft_strncmp(identifier, path_start, ft_strlen(identifier)) == 0)))
	{
		if (path_start == line_content_start && ft_strncmp(identifier, path_start, ft_strlen(identifier)) == 0)
		{
			identifier_occurrences++;
			path_start += ft_strlen(identifier);
		}
		else if(ft_isspace(*path_start))
		{
			path_start++;
		}
		else
			break;
	}

	trim_trailing_whitespace_or_newline(path_start, original_line);

	if (!check_path(path_start) || identifier_occurrences != 1)
	{
		free(original_line);
		handle_error("Error: Invalid texture file path or malformed texture line.\n");
	}
	*target_texture_path_ptr = ft_strdup(path_start);
	if (!*target_texture_path_ptr)
	{
		free(original_line);
		handle_error("Error: Memory allocation failed for texture path (ft_strdup).\n");
	}
	*processed_flag = true;
}

void	trim_trailing_whitespace_or_newline(char *str, char *original_line)
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
			handle_error("Error: Invalid characters found after texture path.\n");
		}
		i++;
	}
	str[path_len] = '\0';
}

void	check_spaces_after_identifier(char *line_content_start, const char *identifier, char *original_line)
{
	size_t	identifier_len;

	identifier_len = ft_strlen(identifier);
	if (ft_strncmp(identifier, line_content_start, identifier_len) == 0 && \
		ft_isspace(line_content_start[identifier_len]))
	{
		return ;
	}
	else
	{
		free(original_line);
		char error_msg[100] = "Error: Missing space after identifier '";
		ft_strlcat(error_msg, identifier, sizeof(error_msg));
		ft_strlcat(error_msg, "'.\n", sizeof(error_msg));
		handle_error(error_msg);
	}
}
