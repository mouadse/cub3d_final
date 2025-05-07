/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:04:44 by msennane          #+#    #+#             */
/*   Updated: 2025/05/07 11:45:52 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_cub3d *game)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < game->img_height / 2)
	{
		x = 0;
		while (x < game->img_width)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, game->data->ceiling);
			x++;
		}
		y++;
	}
	while (y < game->img_height)
	{
		x = 0;
		while (x < game->img_width)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, game->data->floor);
			x++;
		}
		y++;
	}
}
