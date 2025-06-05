/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:32:18 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 12:20:56 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map(int argc, char **argv, t_cub3d *game)
{
	t_validator	validator_data;

	check_arguments(game, argc);
	check_extension(game, argv[1]);
	process_map_file(game, argv[1]);
	init_variables_valid(&validator_data);
	found_tabs(game->config);
	analyze_map_content(game->config, &validator_data);
	check_map_content(game, &validator_data);
	surrounded_by_walls(game, game->config);
}

void	check_arguments(t_cub3d *game, int argc)
{
	if (argc < 2)
	{
		handle_error(ERR_MISSING_MAP, game);
	}
	else if (argc > 2)
	{
		handle_error(ERR_TOO_MANY_ARGS, game);
	}
}

void	check_extension(t_cub3d *game, char *map_file)
{
	const char	*required_extension;
	int			filename_len;
	int			extension_len;

	required_extension = ".cub";
	filename_len = ft_strlen(map_file);
	extension_len = ft_strlen(required_extension);
	if (filename_len < extension_len)
		handle_error(ERR_INVALID_EXTENSION, game);
	if (ft_strcmp(map_file + filename_len - extension_len,
			required_extension) == 0)
		return ;
	handle_error(ERR_INVALID_EXTENSION, game);
}

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
