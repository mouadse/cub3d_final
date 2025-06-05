/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:28:43 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:11:39 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	process_map_line_content(t_cub3d *game, char *current_line_content,
				int current_map_grid_index);

static void	skip_to_map_content(t_cub3d *game, int fd, char **current_line)
{
	*current_line = get_next_line(fd);
	while (*current_line && !is_map_content_line(*current_line))
	{
		free(*current_line);
		*current_line = get_next_line(fd);
	}
	if (!*current_line)
	{
		handle_error(ERR_NO_MAP_CONTENT, game);
		return ;
	}
}

// static bool	process_map_line(t_cub3d *game, char *current_line,
// 		bool *is_map_content_started, bool *is_map_content_ended,
// 		int *current_grid_idx)
// {
// 	if (current_line[0] == '\n')
// 	{
// 		if (*is_map_content_started)
// 			*is_map_content_ended = true;
// 	}
// 	else
// 	{
// 		if (*is_map_content_ended)
// 		{
// 			free(current_line);
// 			handle_error(ERR_MAP_AFTER_EMPTY, game);
// 			return (false);
// 		}
// 		*is_map_content_started = true;
// 		if (process_map_line_content(game, current_line, *current_grid_idx))
// 		{
// 			(*current_grid_idx)++;
// 		}
// 	}
// 	return (true);
// }

// void	read_and_copy_map_content(t_cub3d *game, int fd)
// {
// 	char	*current_line;
// 	int		current_grid_idx;
// 	bool	is_map_content_started;
// 	bool	is_map_content_ended;

// 	skip_to_map_content(game, fd, &current_line);
// 	if (!current_line)
// 		return ;
// 	current_grid_idx = 0;
// 	is_map_content_started = false;
// 	is_map_content_ended = false;
// 	while (current_line)
// 	{
// 		if (!process_map_line(game, current_line, &is_map_content_started,
// 				&is_map_content_ended, &current_grid_idx))
// 			return ;
// 		free(current_line);
// 		current_line = get_next_line(fd);
// 	}
// 	if (game->config && game->config->grid)
// 		game->config->grid[current_grid_idx] = NULL;
// 	if (current_grid_idx == 0)
// 		handle_error(ERR_NO_VALID_MAP, game);
// 	if (game->config)
// 		game->config->grid_rows = current_grid_idx;
// }

static bool	process_map_line(t_cub3d *game, char *current_line, bool flags[2],
		int *current_grid_idx)
{
	bool	*is_map_content_started;
	bool	*is_map_content_ended;

	is_map_content_started = &flags[MAP_STARTED];
	is_map_content_ended = &flags[MAP_ENDED];
	if (current_line[0] == '\n')
	{
		if (*is_map_content_started)
			*is_map_content_ended = true;
	}
	else
	{
		if (*is_map_content_ended)
		{
			free(current_line);
			handle_error(ERR_MAP_AFTER_EMPTY, game);
			return (false);
		}
		*is_map_content_started = true;
		if (process_map_line_content(game, current_line, *current_grid_idx))
			(*current_grid_idx)++;
	}
	return (true);
}

void	read_and_copy_map_content(t_cub3d *game, int fd)
{
	char	*current_line;
	int		current_grid_idx;
	bool	flags[2];

	flags[0] = false;
	flags[1] = false;
	skip_to_map_content(game, fd, &current_line);
	if (!current_line)
		return ;
	current_grid_idx = 0;
	while (current_line)
	{
		if (!process_map_line(game, current_line, flags, &current_grid_idx))
			return ;
		free(current_line);
		current_line = get_next_line(fd);
	}
	if (game->config && game->config->grid)
		game->config->grid[current_grid_idx] = NULL;
	if (current_grid_idx == 0)
		handle_error(ERR_NO_VALID_MAP, game);
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
			handle_error(ERR_FT_STRTRIM_FAIL, game);
			return (false);
		}
		game->config->grid[current_map_grid_index] = trimmed_line;
		return (true);
	}
	else
	{
		handle_error(ERR_MAP_DIMENSIONS, game);
		return (false);
	}
}
