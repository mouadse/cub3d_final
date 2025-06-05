/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:27:04 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:27:52 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

static bool	handle_non_digit_error(t_cub3d *game, char *trim_s,
		t_rgb_error_context *err_ctx)
{
	free(trim_s);
	rgb_parse_err(game, "Error: non-digit.\n", err_ctx->original_line,
		err_ctx->all_components_array);
	return (false);
}

static bool	process_single_rgb_component(t_cub3d *game,
		t_rgb_error_context *err_ctx, char **comp_ptr, int *val)
{
	char	*orig_s;
	char	*trim_s;
	int		j;

	j = 0;
	orig_s = *comp_ptr;
	trim_s = ft_strtrim(orig_s, " \t\v\f\r\n");
	if (!trim_s)
		return (rgb_parse_err(game, "Error: trim fail.\n",
				err_ctx->original_line, err_ctx->all_components_array), false);
	while (trim_s[j])
	{
		if (!ft_isdigit(trim_s[j++]))
			return (handle_non_digit_error(game, trim_s, err_ctx));
	}
	if (j == 0)
		return (free(trim_s), rgb_parse_err(game, "Error: empty component.\n",
				err_ctx->original_line, err_ctx->all_components_array), false);
	*val = ft_atoi(trim_s);
	free(orig_s);
	*comp_ptr = trim_s;
	if (*val < 0 || *val > 255)
		return (rgb_parse_err(game, "Error: range (0-255).\n",
				err_ctx->original_line, err_ctx->all_components_array), false);
	return (true);
}

static int	parse_and_validate_rgb_components(t_cub3d *game,
		t_rgb_parse_args *args, char **rgb_components, int rgb_int_values[3])
{
	int					i;
	t_rgb_error_context	err_ctx;

	err_ctx.original_line = args->original_line;
	err_ctx.all_components_array = rgb_components;
	i = 0;
	while (rgb_components[i])
	{
		if (i >= 3)
		{
			rgb_parse_err(game, "Error: Too many RGB components.\n",
				err_ctx.original_line, err_ctx.all_components_array);
			return (-1);
		}
		if (!process_single_rgb_component(game, &err_ctx, &rgb_components[i],
				&rgb_int_values[i]))
			return (-1);
		i++;
	}
	return (i);
}

static void	parse_rgb_values(t_cub3d *game, t_rgb_parse_args *args)
{
	char	**rgb_components;
	int		rgb_values[3];
	int		count;

	ft_memset(rgb_values, 0, sizeof(rgb_values));
	rgb_components = ft_split(args->rgb_values_str, ',');
	if (!rgb_components)
	{
		rgb_parse_err(game, "Error: ft_split failed for RGB values.\n",
			args->original_line, NULL);
		return ;
	}
	count = parse_and_validate_rgb_components(game, args, rgb_components,
			rgb_values);
	if (count != 3)
		rgb_parse_err(game, "Error: Incorrect RGB component count.\n",
			args->original_line, rgb_components);
	*args->target_color_value = convert_rgb(rgb_values[0], rgb_values[1],
			rgb_values[2]);
	ft_free_matrix(rgb_components);
}

void	check_rgb(t_cub3d *game, t_rgb_params *params)
{
	t_rgb_parse_args	local_parse_args;
	char				*values_ptr;

	validate_rgb_identifier_format(game, params->line_content_start,
		params->original_line, params->identifier_char);
	values_ptr = params->line_content_start + 1;
	while (ft_isspace(*values_ptr))
		values_ptr++;
	local_parse_args.target_color_value = params->target_color_value;
	local_parse_args.rgb_values_str = values_ptr;
	local_parse_args.original_line = params->original_line;
	local_parse_args.identifier_char = params->identifier_char;
	parse_rgb_values(game, &local_parse_args);
	*(params->processed_flag) = true;
}
