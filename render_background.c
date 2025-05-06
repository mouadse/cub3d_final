/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:04:44 by msennane          #+#    #+#             */
/*   Updated: 2025/05/06 18:15:53 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void demo(t_cub3d *game)
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;

	img = mlx_new_image(game->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	game->mlx_image = img;
	game->img_addr = addr;
	game->bits_per_pixel = bits_per_pixel;
	game->line_length = line_length;

	// Draw ceiling (top half of screen)
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			*(unsigned int*)(addr + (y * line_length + x * (bits_per_pixel / 8))) = game->data->ceiling;
			x++;
		}
		y++;
	}
	// Draw floor (bottom half of screen)
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			*(unsigned int*)(addr + (y * line_length + x * (bits_per_pixel / 8))) = game->data->floor;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, 0, 0);
}
