/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:29:10 by msennane          #+#    #+#             */
/*   Updated: 2025/06/04 14:03:10 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Propagated game pointer for handle_error
#include "cub3d.h"

void	get_max_lines(t_config *config)
{
	int	lines;

	lines = 0;
	if (!config || !config->grid)
		return ;
	while (config->grid[lines])
		lines++;
	config->grid_rows = lines;
}

void	get_max_columns(t_config *config)
{
	int	max_cols;
	int	current_cols;
	int	i;

	max_cols = 0;
	i = 0;
	if (!config || !config->grid)
		return ;
	while (config->grid[i])
	{
		current_cols = ft_strlen(config->grid[i]);
		if (current_cols > max_cols)
			max_cols = current_cols;
		i++;
	}
	config->grid_cols = max_cols;
}

void	get_max_columns_with_filepath(t_config *config, char *filepath)
{
	int	max_cols;
	int	current_cols;
	int	fd;
	char	*line_content;

	max_cols = 0;
	if (!config || !filepath)
		return ;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return ;
	line_content = get_next_line(fd);
	while (line_content)
	{
		current_cols = ft_strlen(line_content);
		if (current_cols > max_cols)
			max_cols = current_cols;
		free(line_content);
		line_content = get_next_line(fd);
	}
	close(fd);
	config->grid_cols = max_cols;
}

void	check_map_content(t_cub3d *game, t_validator *validator)
{
	if (validator->invalid_char_count != 0)
		handle_error(ERR_INVALID_CHARACTER, game);
	else if (validator->player_count != 1)
		handle_error(ERR_PLAYER_COUNT, game);
}

int	check_invalid_char(char c)
{
	if (c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0'
		|| c == '1')
		return (1);
	if (c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0'
		|| c == '1' || c == '\0' || c == '\n' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
