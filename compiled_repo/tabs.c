/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:29:34 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:37:44 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"
int	count_tabs(char *line)
{
	int	i;
	int	tabs;

	i = 0;
	tabs = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\t')
			tabs++;
		i++;
	}
	return (tabs);
}

void	found_tabs(t_config *config)
{
	int		i;
	int		num_tabs;
	char	*original_line_ptr;

	i = 0;
	if (!config || !config->grid)
		return;

	while (config->grid[i])
	{
		num_tabs = count_tabs(config->grid[i]);
		if (num_tabs > 0)
		{
			original_line_ptr = config->grid[i];
			config->grid[i] = replace_tabs(original_line_ptr, num_tabs);
			if (!config->grid[i])
			{
				config->grid[i] = original_line_ptr;
				handle_error("Error: Failed to replace tabs in map line (memory allocation issue).\n");
				return;
			}
			free(original_line_ptr);
		}
		i++;
	}
}

char	*replace_tabs(char *line, int num_tabs)
{
	char	*replaced_line;
	int		original_idx;
	int		new_idx;
	int		space_idx;
	const int tab_width = 4;

	original_idx = 0;
	new_idx = 0;
	replaced_line = ft_calloc(sizeof(char), (ft_strlen(line) - num_tabs + (num_tabs * tab_width) + 1));
	if (!replaced_line)
		return (NULL);

	while (line[original_idx])
	{
		if (line[original_idx] == '\t')
		{
			space_idx = 0;
			while (space_idx < tab_width)
			{
				replaced_line[new_idx++] = ' ';
				space_idx++;
			}
			original_idx++;
		}
		else
		{
			replaced_line[new_idx++] = line[original_idx++];
		}
	}
	return (replaced_line);
}
