/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:30:07 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 21:00:46 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static t_cub3d	*g_game_instance = NULL;

void	init_game_instance(t_cub3d *game_ptr)
{
	if (g_game_instance == NULL && game_ptr != NULL)
		g_game_instance = game_ptr;
}

t_cub3d	*get_game(void)
{
	return (g_game_instance);
}

void	handle_error(char *message)
{
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	else
		ft_putstr_fd("Error: An unknown error occurred.\n", STDERR_FILENO);
	free_memory(get_game());
	exit(EXIT_FAILURE);
}

int	open_file(char *map_file)
{
	int		fd;
	char	error_msg[100] = "Error: could not open file: ";

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		ft_strlcat(error_msg, map_file, sizeof(error_msg));
		ft_strlcat(error_msg, "\n", sizeof(error_msg));
		handle_error(error_msg);
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

static void	free_single_texture(void *mlx_ptr, t_tex *texture)
{
	if (texture)
	{
		if (texture->ptr && mlx_ptr)
		{
			mlx_destroy_image(mlx_ptr, texture->ptr);
		}
		free(texture);
	}
}

void	free_memory(t_cub3d *game)
{
	if (!game)
		return;
	if (game->config)
	{
		if (game->config->no_texture_path)
			free(game->config->no_texture_path);
		if (game->config->so_texture_path)
			free(game->config->so_texture_path);
		if (game->config->we_texture_path)
			free(game->config->we_texture_path);
		if (game->config->ea_texture_path)
			free(game->config->ea_texture_path);
		if (game->config->grid)
			ft_free_matrix(game->config->grid);
	}
	if (game->mlx)
	{
		free_single_texture(game->mlx, game->north_texture);
		free_single_texture(game->mlx, game->south_texture);
		free_single_texture(game->mlx, game->west_texture);
		free_single_texture(game->mlx, game->east_texture);
	}
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->texture = NULL;
	if (game->img.ptr && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img.ptr);
		game->img.ptr = NULL;
	}
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	#ifdef __linux__
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
	}
	#endif
	if (game->mlx)
	{
		free(game->mlx);
		game->mlx = NULL;
	}
	if (g_game_instance == game)
	{
		g_game_instance = NULL;
	}
}
