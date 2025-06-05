/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_identifiers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:26:42 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:24:45 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_spaces_after_identifier(t_cub3d *game, char *line_content_start,
		const char *identifier, char *original_line)
{
	size_t	identifier_len;

	identifier_len = ft_strlen(identifier);
	if (ft_strncmp(identifier, line_content_start, identifier_len) == 0
		&& ft_isspace(line_content_start[identifier_len]))
	{
		return ;
	}
	else
	{
		free(original_line);
		handle_error("Error: Missing space after identifier.\n", game);
	}
}

void	trim_trailing_whitespace_or_newline(t_cub3d *game, char *str,
		char *original_line)
{
	size_t	i;
	size_t	path_len;

	path_len = 0;
	while (str[path_len] && !ft_isspace(str[path_len]))
		path_len++;
	i = path_len;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isspace(str[i]))
		{
			free(original_line);
			handle_error(ERR_TRAILING_CHARS, game);
		}
		i++;
	}
	str[path_len] = '\0';
}

void	validate_texture_preconditions(t_cub3d *game,
		const t_texture_args *args)
{
	if (*(args->target_texture_path_ptr) != NULL)
	{
		free(args->original_line);
		handle_error(ERR_DUPLICATE_TEXTURE_PATH, game);
	}
	check_spaces_after_identifier(game, args->line_content_start,
		args->identifier, args->original_line);
}

char	*skip_identifier_and_spaces(const t_texture_args *args,
		int *identifier_occurrences)
{
	char	*path_start;

	path_start = args->line_content_start;
	*identifier_occurrences = 0;
	while (*path_start && (ft_isspace(*path_start)
			|| (path_start == args->line_content_start
				&& ft_strncmp(args->identifier, path_start,
					ft_strlen(args->identifier)) == 0)))
	{
		if (path_start == args->line_content_start
			&& ft_strncmp(args->identifier, path_start,
				ft_strlen(args->identifier)) == 0)
		{
			(*identifier_occurrences)++;
			path_start += ft_strlen(args->identifier);
		}
		else if (ft_isspace(*path_start))
			path_start++;
		else
			break ;
	}
	return (path_start);
}

char	*extract_and_validate_path_segment(t_cub3d *game,
		const t_texture_args *args)
{
	char	*path_start;
	int		identifier_occurrences;

	path_start = skip_identifier_and_spaces(args, &identifier_occurrences);
	trim_trailing_whitespace_or_newline(game, path_start, args->original_line);
	if (!check_path(path_start) || identifier_occurrences != 1)
	{
		free(args->original_line);
		handle_error(ERR_INVALID_TEXTURE_PATH, game);
		return (NULL);
	}
	return (path_start);
}
