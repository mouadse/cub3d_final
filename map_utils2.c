/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:28:43 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 13:47:10 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		handle_error("Calloc failed for map grid\n", game);
	game->config->grid_rows = total_lines_in_file;
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

bool	is_map_content_line(char *line)
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
