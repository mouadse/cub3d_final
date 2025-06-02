/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:27:53 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:43:16 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static int	has_valid_neighbors(t_config *config, int row, int col)
{
	if (row <= 0 || row >= config->grid_rows - 1 || \
		col <= 0 || col >= config->grid_cols -1)
		return (0);

	if (config->grid[row][col + 1] == ' ' || \
		config->grid[row][col - 1] == ' ' || \
		config->grid[row + 1][col] == ' ' || \
		config->grid[row - 1][col] == ' ')
		return (0);
	return (1);
}

static int	validate_map_cell_rules(t_config *config, int row, int col)
{
	char	cell_char;

	cell_char = config->grid[row][col];

	if (row == 0 || row == config->grid_rows - 1 || \
		col == 0 || col == config->grid_cols - 1)
	{
		if (cell_char != '1' && cell_char != ' ' && cell_char != '2')
			return (0);
	}
	else if (cell_char == '0' || ft_strchr("NSWE", cell_char))
	{
		if (!has_valid_neighbors(config, row, col))
			return (0);
	}
	return (1);
}

static int	is_map_structurally_sound(t_config *config)
{
	int	row_idx;
	int	col_idx;

	row_idx = 0;
	while (row_idx < config->grid_rows)
	{
		col_idx = 0;
		while (col_idx < config->grid_cols && config->grid[row_idx][col_idx])
		{
			if (!validate_map_cell_rules(config, row_idx, col_idx))
				return (0);
			col_idx++;
		}
		row_idx++;
	}
	return (1);
}

int	is_map_enclosed(t_config *config)
{
	return (is_map_structurally_sound(config));
}

void	surrounded_by_walls(t_config *config)
{
	if (!is_map_enclosed(config))
		handle_error("Error: Map is not correctly enclosed by walls or has invalid bordering characters.\n");
}
