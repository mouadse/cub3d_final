/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:26:42 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 11:48:24 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_texture_path_line(t_cub3d *game, t_texture_args *args,
		bool *processed_successfully)
{
	if (ft_strncmp("NO", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->no_texture_path);
		args->identifier = "NO";
	}
	else if (ft_strncmp("SO", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->so_texture_path);
		args->identifier = "SO";
	}
	else if (ft_strncmp("WE", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->we_texture_path);
		args->identifier = "WE";
	}
	else if (ft_strncmp("EA", args->line_content_start, 2) == 0)
	{
		args->target_texture_path_ptr = &(game->config->ea_texture_path);
		args->identifier = "EA";
	}
	else
		return ;
	copy_texture_path(game, args, processed_successfully);
}

bool	process_texture_identifiers(t_cub3d *game, char *trimmed_line_start,
		char *original_line, bool *processed_successfully)
{
	t_texture_args	args;

	if (ft_strncmp("NO", trimmed_line_start, 2) == 0 || ft_strncmp("SO",
			trimmed_line_start, 2) == 0 || ft_strncmp("WE", trimmed_line_start,
			2) == 0 || ft_strncmp("EA", trimmed_line_start, 2) == 0)
	{
		args.line_content_start = trimmed_line_start;
		args.original_line = original_line;
		handle_texture_path_line(game, &args, processed_successfully);
		return (true);
	}
	return (false);
}

bool	process_texture_line(t_cub3d *game, char *trimmed_line_start,
		char *original_line, bool *processed_successfully)
{
	if (process_texture_identifiers(game, trimmed_line_start, original_line,
			processed_successfully))
		return (true);
	if (process_color_identifiers(game, trimmed_line_start, original_line,
			processed_successfully))
		return (true);
	return (false);
}

void	copy_texture_path(t_cub3d *game, const t_texture_args *args,
		bool *processed_flag)
{
	char	*valid_path_segment;

	validate_texture_preconditions(game, args);
	valid_path_segment = extract_and_validate_path_segment(game, args);
	*(args->target_texture_path_ptr) = ft_strdup(valid_path_segment);
	if (!*(args->target_texture_path_ptr))
	{
		free(args->original_line);
		handle_error(ERR_TEXTURE_ALLOC, game);
	}
	*processed_flag = true;
}
