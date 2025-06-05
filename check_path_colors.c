/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:26:42 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 11:34:19 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_rgb_line(t_cub3d *game, t_rgb_params *params)
{
	check_rgb(game, params);
}

bool	process_color_identifiers(t_cub3d *game, char *trimmed_line_start,
		char *original_line, bool *processed_successfully)
{
	t_rgb_params	rgb_params;

	if (ft_strncmp("F", trimmed_line_start, 1) == 0)
	{
		rgb_params.target_color_value = &game->config->floor_rgb;
		rgb_params.line_content_start = trimmed_line_start;
		rgb_params.original_line = original_line;
		rgb_params.identifier_char = 'F';
		rgb_params.processed_flag = processed_successfully;
		handle_rgb_line(game, &rgb_params);
		return (true);
	}
	else if (ft_strncmp("C", trimmed_line_start, 1) == 0)
	{
		rgb_params.target_color_value = &game->config->ceiling_rgb;
		rgb_params.line_content_start = trimmed_line_start;
		rgb_params.original_line = original_line;
		rgb_params.identifier_char = 'C';
		rgb_params.processed_flag = processed_successfully;
		handle_rgb_line(game, &rgb_params);
		return (true);
	}
	return (false);
}

void	check_colors_loaded_count(t_cub3d *game, t_config *config,
		const char *original_line, const char *trimmed_line_start)
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
		handle_error("Error: Duplicate color definition (Floor or Ceiling).\n",
			game);
	}
}
