/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:27:53 by msennane          #+#    #+#             */
/*   Updated: 2025/04/10 12:28:25 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_map_with_twos(t_config *config);
static int	count_len(char *str);
bool	check_diagonals(t_config *config, int line, int col)
{
	char	**grid;

	grid = config->grid;
	if (line > 0 && col > 0 && (grid[line - 1][col - 1] == ' ' || grid[line
			- 1][col - 1] == '2'))
		return (false);
	if (line + 1 < config->grid_rows && col > 0 && (grid[line + 1][col
			- 1] == ' ' || grid[line + 1][col - 1] == '2'))
		return (false);
	if (line > 0 && col + 1 < config->grid_cols && (grid[line - 1][col
			+ 1] == ' ' || grid[line - 1][col + 1] == '2'))
		return (false);
	if (line + 1 < config->grid_rows && col + 1 < config->grid_cols
		&& (grid[line + 1][col + 1] == ' ' || grid[line + 1][col + 1] == '2'))
		return (false);
	return (true);
}

bool	check_sides(t_config *config, int line, int col)
{
	char	**grid;

	grid = config->grid;
	if (line <= 0 || line >= config->grid_rows || col <= 0
		|| col >= config->grid_cols)
		return (false);
	if (line > 0 && (grid[line - 1][col] == ' ' || grid[line - 1][col] == '2'))
		return (false);
	if (line + 1 < config->grid_rows && (grid[line + 1][col] == ' ' || grid[line
			+ 1][col] == '2'))
		return (false);
	if (col > 0 && (grid[line][col - 1] == ' ' || grid[line][col - 1] == '2'))
		return (false);
	if (col + 1 < config->grid_cols && (grid[line][col + 1] == ' '
			|| grid[line][col + 1] == '2'))
		return (false);
	return (true);
}

void	surrounded_by_walls(t_config *config)
{
	char	**grid;
	int		y;
	int		x;

	y = 0;
	fill_map_with_twos(config);
	grid = config->grid;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '0' || ft_strchr("NSWE", grid[y][x]))
			{
				if ((y == 0 || y == config->grid_rows - 1) || (x == 0
						|| x == count_len(grid[y]) - 1))
					handle_error("Error: invalid map, check the edges.\n");
				if (!check_sides(config, y, x) || !check_diagonals(config, y,
						x))
					handle_error("Error: invalid map, check the walls.\n");
			}
			x++;
		}
		y++;
	}
}

static void	fill_map_with_twos(t_config *config)
{
	size_t	i;
	size_t	j;
	char	**new_grid;

	i = 0;
	new_grid = ft_calloc(config->grid_rows + 1, sizeof(char *));
	while (i < (size_t)config->grid_rows)
	{
		j = 0;
		new_grid[i] = ft_calloc((config->grid_cols + 1), sizeof(char));
		while (j < ft_strlen(config->grid[i]) - 1)
		{
			new_grid[i][j] = config->grid[i][j];
			j++;
		}
		while (j < (size_t)config->grid_cols)
		{
			new_grid[i][j] = '2';
			j++;
		}
		i++;
	}
	ft_free_matrix(config->grid);
	config->grid = new_grid;
}

static int	count_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '2')
		i++;
	return (i);
}
