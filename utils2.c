/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:30:07 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 12:17:18 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdio.h>

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	init_variables_valid(t_validator *validator)
{
	validator->invalid_char_count = 0;
	validator->player_count = 0;
}

void	handle_error(char *message, t_cub3d *game)
{
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	cleanup_get_next_line();
	free_memory(game);
	exit(EXIT_FAILURE);
}

int	open_file(char *map_file, t_cub3d *game)
{
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Failed to open map file: ", STDERR_FILENO);
		ft_putstr_fd(map_file, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		handle_error(NULL, game);
	}
	return (fd);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
