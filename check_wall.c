/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:27:53 by msennane          #+#    #+#             */
/*   Updated: 2025/04/10 14:38:37 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	fill_map_with_twos(t_config *config);
// static int	count_len(char *str);
// bool	check_diagonals(t_config *config, int line, int col)
// {
// 	char	**grid;

// 	grid = config->grid;
// 	if (line > 0 && col > 0 && (grid[line - 1][col - 1] == ' ' || grid[line
// 			- 1][col - 1] == '2'))
// 		return (false);
// 	if (line + 1 < config->grid_rows && col > 0 && (grid[line + 1][col
// 			- 1] == ' ' || grid[line + 1][col - 1] == '2'))
// 		return (false);
// 	if (line > 0 && col + 1 < config->grid_cols && (grid[line - 1][col
// 			+ 1] == ' ' || grid[line - 1][col + 1] == '2'))
// 		return (false);
// 	if (line + 1 < config->grid_rows && col + 1 < config->grid_cols
// 		&& (grid[line + 1][col + 1] == ' ' || grid[line + 1][col + 1] ==
// '2')) 		return (false); 	return (true);
// }

// bool	check_sides(t_config *config, int line, int col)
// {
// 	char	**grid;

// 	grid = config->grid;
// 	/* Removed this incorrect boundary check:
// 	if (line <= 0 || line >= config->grid_rows || col <= 0
// 		|| col >= config->grid_cols)
// 		return (false);
// 	*/
// 	if (line <= 0 || line >= config->grid_rows || col <= 0
// 		|| col >= config->grid_cols)
// 		return (false);
// 	if (line > 0 && (grid[line - 1][col] == ' ' || grid[line - 1][col] ==
// '2')) 		return (false); 	if (line + 1 < config->grid_rows && (grid[line +
// 1][col] == ' ' || grid[line
// 			+ 1][col] == '2'))
// 		return (false);
// 	if (col > 0 && (grid[line][col - 1] == ' ' || grid[line][col - 1] ==
// '2')) 		return (false); 	if (col + 1 < config->grid_cols && (grid[line][col + 1]
// == ' '
// 			|| grid[line][col + 1] == '2'))
// 		return (false);
// 	return (true);
// }

// void	surrounded_by_walls(t_config *config)
// {
// 	char	**grid;
// 	int		y;
// 	int		x;

// 	y = 0;
// 	fill_map_with_twos(config);
// 	grid = config->grid;
// 	while (grid[y])
// 	{
// 		x = 0;
// 		while (grid[y][x])
// 		{
// 			if (grid[y][x] == '0' || ft_strchr("NSWE", grid[y][x]))
// 			{
// 				if ((y == 0 || y == config->grid_rows - 1) || (x
// == 0
// 						|| x == count_len(grid[y]) - 1))
// 					handle_error("Error: invalid map, check
// the edges.\n"); 				if (!check_sides(config, y, x) || !check_diagonals(config, y,
// 						x))
// 					handle_error("Error: invalid map, check
// the walls.\n");
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	fill_map_with_twos(t_config *config)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	**new_grid;

// 	i = 0;
// 	new_grid = ft_calloc(config->grid_rows + 1, sizeof(char *));
// 	while (i < (size_t)config->grid_rows)
// 	{
// 		j = 0;
// 		new_grid[i] = ft_calloc((config->grid_cols + 1), sizeof(char));
// 		while (j < ft_strlen(config->grid[i]) - 1)
// 		{
// 			new_grid[i][j] = config->grid[i][j];
// 			j++;
// 		}
// 		while (j < (size_t)config->grid_cols)
// 		{
// 			new_grid[i][j] = '2';
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_free_matrix(config->grid);
// 	config->grid = new_grid;
// }

// static int	count_len(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != '2')
// 		i++;
// 	return (i);
// }

static int has_valid_neighbors(t_config *config, int i, int j) {
  if (config->grid[i][j + 1] == ' ' || config->grid[i][j - 1] == ' ' ||
      config->grid[i + 1][j] == ' ' || config->grid[i - 1][j] == ' ')
    return (0);
  return (1);
}


static int validate_map_element(t_config *config, int i, int j)
{
	char c;

	c = config->grid[i][j];
	if (i == 0 || i == config->grid_rows - 1 || j == 0 || j == config->grid_cols - 1)
	{
		// Elements at map borders must be walls or spaces
		if (c != '1' && c != ' ' && c != '2')
			return (0);
	}
	else if (c == '0' || ft_strchr("NSWE", c))
	{
		// Playable spaces and player positions must have valid neighbors
		if (!has_valid_neighbors(config, i, j))
			return (0);
	}
	return (1);
}

static int is_enclosed_map(t_config *config)
{
	int i;
	int j;

	i = 0;
	while (i < config->grid_rows)
	{
		j = 0;
		while (j < config->grid_cols && config->grid[i][j])
		{
			if (!validate_map_element(config, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int is_map_enclosed(t_config *config)
{
	return is_enclosed_map(config);
}


void	surrounded_by_walls(t_config *config)
{
	if (!is_map_enclosed(config))
		handle_error("Error: invalid map, check the walls.\n");
}
