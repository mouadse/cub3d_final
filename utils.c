/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:30:07 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:16:15 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

char	*extract_line(t_list *node)
{
	char				*line;
	int					i;
	struct s_list_node	*temp;

	i = 0;
	temp = node->head;
	while (temp && temp->data != '\n')
	{
		temp = temp->next;
		i++;
	}
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (node->head && node->head->data != '\n')
		line[i++] = pop_node(node);
	line[i++] = pop_node(node);
	line[i] = '\0';
	return (line);
}

int	is_it_empty(t_list *node)
{
	return (node->head == NULL);
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

static void	free_config_and_textures(t_cub3d *game)
{
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
}

void	free_memory(t_cub3d *game)
{
	if (!game)
		return ;
	free_config_and_textures(game);
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
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
