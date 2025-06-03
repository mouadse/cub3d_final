/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:28:43 by msennane          #+#    #+#             */
/*   Updated: 2025/06/03 13:32:54 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Propagated game pointer for handle_error and removed get_game()
#include "cub3d.h"

static bool	process_map_line_content(t_cub3d *game, char *current_line_content,
				int current_map_grid_index);

static bool	is_map_content_line(char *line);

void	count_map_size(t_cub3d *game, char *map_file_path)
{
	int		total_lines_in_file;
	char	*line_content;
	int		fd;

	fd = open_file(map_file_path, game);
	total_lines_in_file = 0;
	line_content = get_next_line(fd);
	while (line_content)
	{
		total_lines_in_file++;
		free(line_content);
		line_content = get_next_line(fd);
	}
	close(fd);
	if (total_lines_in_file == 0)
		handle_error("Error: Map file is empty or could not be read.\n", game);
	game->config->grid = ft_calloc(sizeof(char *), (total_lines_in_file + 1));
	if (!game->config->grid)
		handle_error("Error: Memory allocation failed for map grid (ft_calloc).\n", game);
	game->config->grid_rows = total_lines_in_file;
}

void	read_and_copy_map_content(t_cub3d *game, int fd)
{
	char	*current_line;
	int		map_lines_processed_count;
	int		current_grid_idx;
	bool	is_map_content_started;
	bool	is_map_content_ended;

	current_line = get_next_line(fd);
	while (current_line && !is_map_content_line(current_line))
	{
		free(current_line);
		current_line = get_next_line(fd);
	}
	if (!current_line)
	{
		handle_error("Error: No map content found in file.\n", game);
		return ;
	}
	map_lines_processed_count = 0;
	current_grid_idx = 0;
	is_map_content_started = false;
	is_map_content_ended = false;
	while (current_line)
	{
		if (current_line[0] == '\n')
		{
			if (is_map_content_started)
				is_map_content_ended = true;
		}
		else
		{
			if (is_map_content_ended)
			{
				free(current_line);
				handle_error("Error: Map content found after an empty line separator,indicating invalid map structure.\n", game);
				return ; // This line never executes due to handle_error's exit()
			}
			is_map_content_started = true;
			if (process_map_line_content(game, current_line, current_grid_idx))
			{
				current_grid_idx++;
			}
		}
		map_lines_processed_count++;
		free(current_line);
		current_line = get_next_line(fd);
	}
	if (game->config && game->config->grid)
	{
		game->config->grid[current_grid_idx] = NULL;
	}
	if (current_grid_idx == 0)
	{
		handle_error("Error: No valid map content found after texture definitions.\n", game);
	}
	if (game->config)
		game->config->grid_rows = current_grid_idx;
}

static bool	process_map_line_content(t_cub3d *game, char *current_line_content,
		int current_map_grid_index)
{
	char	*trimmed_line;

	if (current_map_grid_index < game->config->grid_rows)
	{
		trimmed_line = ft_strtrim(current_line_content, "\n");
		if (!trimmed_line)
		{
			handle_error("Error: ft_strtrim failed during map processing due to allocation failure.\n", game);
			return (false);
		}
		game->config->grid[current_map_grid_index] = trimmed_line;
		return (true);
	}
	else
	{
		handle_error("Error: Map dimensions exceed pre-calculated size. Mismatched map row count or invalid map structure.\n", game);
		return (false);
	}
}

void	analyze_map_content(t_config *config, t_validator *validator)
{
	int	i;
	int	j;

	i = 0;
	while (config->grid[i])
	{
		j = 0;
		while (config->grid[i][j])
		{
			if (check_invalid_char(config->grid[i][j]) == 0)
				validator->invalid_char_count++;
			else if (config->grid[i][j] == 'N' || config->grid[i][j] == 'S'
				|| config->grid[i][j] == 'E' || config->grid[i][j] == 'W')
			{
				validator->player_count++;
				config->character_orientation = config->grid[i][j];
				config->character_pos_y = i;
				config->character_pos_x = j;
			}
			j++;
		}
		i++;
	}
}

static bool	is_map_content_line(char *line)
{
	int		i;
	char	c;

	if (!line)
		return (false);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (false);
	if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA",
			2) == 0 || ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i],
			"C", 1) == 0)
		return (false);
	while (line[i] && line[i] != '\n')
	{
		c = line[i];
		if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E'
			|| c == 'W')
			return (true);
		i++;
	}
	return (false);
}
