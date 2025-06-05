/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:26:42 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 11:50:38 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture_file_path(t_cub3d *game, t_config *config,
		char *trimmed_line_start, char *original_line)
{
	bool	processed_successfully;
	bool	identifier_found;

	(void)config;
	processed_successfully = false;
	identifier_found = process_texture_line(game, trimmed_line_start,
			original_line, &processed_successfully);
	if (identifier_found)
	{
		if (processed_successfully)
		{
			game->config->loaded_textures++;
			check_colors_loaded_count(game, game->config, original_line,
				trimmed_line_start);
		}
	}
	else
	{
		if (trimmed_line_start[0] != '\n' && trimmed_line_start[0] != '\0')
		{
			free(original_line);
			handle_error(ERR_INVALID_IDENTIFIER, game);
		}
	}
}
