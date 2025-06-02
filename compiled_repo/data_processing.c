/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:31:51 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:42:19 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_file(char *map_file, t_config *config)
{
	int		fd;

	fd = open_file(map_file);
	read_textures_path(config, NULL, fd);
	close(fd);

	count_map_size(config, map_file);

	fd = open_file(map_file);
	read_and_copy_map_content(fd);
	close(fd);

	if (config->grid == NULL || config->grid[0] == NULL)
		handle_error("Error: Map grid is empty or was not loaded correctly.\n");

	get_max_columns(config);
	get_max_lines(config);
}

void	read_textures_path(t_config *config, char *unused_temp_param, int fd)
{
	char	*line_content;
	char	*current_line_trimmed_start;

	(void)unused_temp_param;

	line_content = get_next_line(fd);
	while (line_content)
	{
		current_line_trimmed_start = line_content;
		while (ft_isspace(*current_line_trimmed_start))
			current_line_trimmed_start++;

		if (*current_line_trimmed_start != '\0')
			parse_texture_file_path(config, current_line_trimmed_start, line_content);
		free(line_content);

		if (config->no_texture_path && config->so_texture_path
			&& config->we_texture_path && config->ea_texture_path
			&& config->textures_ready)
			break ;
		line_content = get_next_line(fd);
	}

	if (!(config->no_texture_path && config->so_texture_path
			&& config->we_texture_path && config->ea_texture_path
			&& config->textures_ready))
	{
		if (line_content)
			free(line_content);
		handle_error("Error: Missing one or more texture/color definitions in the map file.\n");
	}
}
