/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:17:23 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:24:23 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	*set_wall(t_cub3d *game, t_dda *ray)
{
	if (ray->hit_side == 1)
	{
		if (ray->step.y < 0)
			return (game->north_texture);
		else
			return (game->south_texture);
	}
	else
	{
		if (ray->step.x < 0)
			return (game->west_texture);
		else
			return (game->east_texture);
	}
	return (NULL);
}

t_tex	*init_texture_data(void)
{
	t_tex	*texture_data;

	texture_data = malloc(sizeof(t_tex));
	if (!texture_data)
	{
		ft_putstr_fd("Error: Memory allocation failed for t_tex structure.\n",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	texture_data->ptr = NULL;
	texture_data->addr = NULL;
	return (texture_data);
}

static void	handle_addr_error(void *mlx, t_tex *texture_data, char *file)
{
	ft_putstr_fd(MLX_ADDR_ERR, STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	mlx_destroy_image(mlx, texture_data->ptr);
	free(texture_data);
	exit(EXIT_FAILURE);
}

t_tex	*load_xpm(void *mlx, char *file, t_cub3d *game)
{
	t_tex	*texture_data;

	texture_data = init_texture_data();
	texture_data->ptr = mlx_xpm_file_to_image(mlx, file, &texture_data->w,
			&texture_data->h);
	if (!texture_data->ptr)
	{
		ft_putstr_fd("Error: Failed to load texture: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(texture_data);
		if (game)
			handle_error("Error: Texture loading failed.\n", game);
		else
			ft_putstr_fd("Error: Game not initialized.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	texture_data->addr = mlx_get_data_addr(texture_data->ptr,
			&texture_data->bpp, &texture_data->line_len, &texture_data->endian);
	if (!texture_data->addr)
	{
		handle_addr_error(mlx, texture_data, file);
	}
	return (texture_data);
}

void	load_textures(t_cub3d *game)
{
	if (!game || !game->config || !game->mlx)
	{
		handle_error(LOAD_TEXTURES_ERR, game);
		return ;
	}
	game->north_texture = load_xpm(game->mlx, game->config->no_texture_path,
			game);
	game->south_texture = load_xpm(game->mlx, game->config->so_texture_path,
			game);
	game->west_texture = load_xpm(game->mlx, game->config->we_texture_path,
			game);
	game->east_texture = load_xpm(game->mlx, game->config->ea_texture_path,
			game);
}
