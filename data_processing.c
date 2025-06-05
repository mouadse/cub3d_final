/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:31:51 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 12:20:47 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_file(t_cub3d *game, char *map_file)
{
	int	fd;

	fd = open_file(map_file, game);
	read_textures_path(game, fd);
	close(fd);
	count_map_size(game, map_file);
	fd = open_file(map_file, game);
	read_and_copy_map_content(game, fd);
	close(fd);
	if (game->config->grid == NULL || game->config->grid[0] == NULL)
		handle_error("Error: Map grid is empty or was not loaded correctly.\n",
			game);
	get_max_columns(game->config);
	get_max_lines(game->config);
}

static void	proc_texture_line(t_cub3d *game, char *line_content)
{
	char	*current_line_trimmed_start;

	current_line_trimmed_start = line_content;
	while (ft_isspace(*current_line_trimmed_start))
		current_line_trimmed_start++;
	if (*current_line_trimmed_start != '\0')
		parse_texture_file_path(game, game->config, current_line_trimmed_start,
			line_content);
}

void	read_textures_path(t_cub3d *game, int fd)
{
	char	*line_content;

	line_content = get_next_line(fd);
	while (line_content)
	{
		if (is_map_content_line(line_content))
		{
			free(line_content);
			break ;
		}
		proc_texture_line(game, line_content);
		free(line_content);
		line_content = get_next_line(fd);
	}
	if (!(game->config->no_texture_path && game->config->so_texture_path
			&& game->config->we_texture_path && game->config->ea_texture_path
			&& game->config->textures_ready))
		handle_error(ERR_MISSING_TEXTURES, game);
}
