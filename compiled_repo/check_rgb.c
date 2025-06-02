/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:27:04 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:43:51 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_rgb_parsing_error(const char *error_message,
				char *original_line_to_free, char **rgb_components_to_free);

static void	validate_rgb_identifier_format(const char *line_content_start,
		char *original_line, char identifier_char)
{
	int			identifier_char_count;
	int			space_after_identifier_count;
	const char	*line_ptr;
		char error_msg[100];

	identifier_char_count = 0;
	space_after_identifier_count = 0;
	line_ptr = line_content_start;
	if (*line_ptr == identifier_char)
	{
		identifier_char_count++;
		line_ptr++;
		if (ft_isspace(*line_ptr))
		{
			while (ft_isspace(*line_ptr))
			{
				space_after_identifier_count++;
				line_ptr++;
			}
		}
	}
	if (identifier_char_count != 1 || space_after_identifier_count == 0)
	{
		ft_strlcpy(error_msg, "Error: Malformed RGB line for '",
			sizeof(error_msg));
		error_msg[ft_strlen(error_msg) + 1] = '\0';
		error_msg[ft_strlen(error_msg)] = identifier_char;
		ft_strlcat(error_msg, "'. Ensure format is 'C R,G,B'.\n",
			sizeof(error_msg));
		handle_rgb_parsing_error(error_msg, original_line, NULL);
	}
}

void	check_rgb(uint32_t *target_color_value, char *line_content_start,
		char *original_line, char identifier_char, bool *processed_flag)
{
	char	**rgb_components;
	char	*rgb_values_str;
	int		rgb_int_values[3];
	int		i;
	int		j;
	char	*trimmed_component;

	validate_rgb_identifier_format(line_content_start, original_line,
		identifier_char);
	rgb_values_str = line_content_start + 1;
	while (ft_isspace(*rgb_values_str))
		rgb_values_str++;
	rgb_components = ft_split(rgb_values_str, ',');
	if (!rgb_components)
	{
		handle_rgb_parsing_error("Error: Memory allocation failed during RGB parsing (ft_split).\n",
			original_line, NULL);
		return ;
	}
	i = 0;
	while (rgb_components[i])
	{
		if (i >= 3)
			handle_rgb_parsing_error("Error: Too many components for RGB color (expecting R,G,B).\n",
				original_line, rgb_components);
		trimmed_component = ft_strtrim(rgb_components[i], " \t\v\f\r\n");
		if (!trimmed_component)
			handle_rgb_parsing_error("Error: Memory allocation failed for RGB component trim.\n",
				original_line, rgb_components);
		free(rgb_components[i]);
		rgb_components[i] = trimmed_component;
		j = 0;
		while (trimmed_component[j])
		{
			if (!ft_isdigit(trimmed_component[j]))
				handle_rgb_parsing_error("Error: Non-digit character found in RGB component.\n",
					original_line, rgb_components);
			j++;
		}
		if (j == 0)
			handle_rgb_parsing_error("Error: Empty RGB component.\n",
				original_line, rgb_components);
		rgb_int_values[i] = ft_atoi(trimmed_component);
		if (rgb_int_values[i] < 0 || rgb_int_values[i] > 255)
			handle_rgb_parsing_error("Error: RGB component value out of range (0-255).\n",
				original_line, rgb_components);
		i++;
	}
	if (i != 3)
		handle_rgb_parsing_error("Error: Not enough components for RGB color (expecting R,G,B).\n",
			original_line, rgb_components);
	*target_color_value = convert_rgb(rgb_int_values[0], rgb_int_values[1],
			rgb_int_values[2]);
	ft_free_matrix(rgb_components);
	*processed_flag = true;
}

uint32_t	convert_rgb(int r, int g, int b)
{
	return (0 << 24 | (uint32_t)r << 16 | (uint32_t)g << 8 | (uint32_t)b);
}

static void	handle_rgb_parsing_error(const char *error_message,
		char *original_line_to_free, char **rgb_components_to_free)
{
	if (original_line_to_free)
		free(original_line_to_free);
	if (rgb_components_to_free)
		ft_free_matrix(rgb_components_to_free);
	handle_error((char *)error_message);
}
