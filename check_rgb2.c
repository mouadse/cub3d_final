/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:27:04 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 13:28:57 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	trigger_rgb_format_error(t_cub3d *game, char *original_line,
		char identifier_char)
{
	char	error_msg[128];
	char	identifier_str[2];

	ft_strlcpy(error_msg, "Error: Malformed RGB line for '", sizeof(error_msg));
	identifier_str[0] = identifier_char;
	identifier_str[1] = '\0';
	ft_strlcat(error_msg, identifier_str, sizeof(error_msg));
	ft_strlcat(error_msg, "'. Expected format: '", sizeof(error_msg));
	ft_strlcat(error_msg, identifier_str, sizeof(error_msg));
	ft_strlcat(error_msg, " R,G,B'.\n", sizeof(error_msg));
	rgb_parse_err(game, error_msg, original_line, NULL);
}

void	validate_rgb_identifier_format(t_cub3d *game,
		const char *line_content_start, char *original_line,
		char identifier_char)
{
	const char	*line_ptr;

	line_ptr = line_content_start;
	if (*line_ptr == identifier_char)
	{
		line_ptr++;
		if (ft_isspace(*line_ptr))
		{
			while (ft_isspace(*line_ptr))
				line_ptr++;
			return ;
		}
	}
	trigger_rgb_format_error(game, original_line, identifier_char);
}

uint32_t	convert_rgb(int r, int g, int b)
{
	return (0 << 24 | (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
}

void	rgb_parse_err(t_cub3d *game, const char *error_message,
		char *original_line_to_free, char **rgb_components_to_free)
{
	if (original_line_to_free)
		free(original_line_to_free);
	if (rgb_components_to_free)
		ft_free_matrix(rgb_components_to_free);
	handle_error((char *)error_message, game);
}
