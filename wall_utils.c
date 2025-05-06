/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:06:49 by msennane          #+#    #+#             */
/*   Updated: 2025/05/06 15:43:22 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall(t_cub3d *game, int pixel, t_wall_slice *wall)
{
	int	y;
	int	color;
	int	texture_y;

	y = wall->line_start_y;
	while (y < wall->line_end_y)
	{
		texture_y = (int)wall->texture_pos & (TEXTURE_SIZE - 1);
		wall->texture_pos += wall->texture_step;
		color = game->texture_pixels[game->texture][TEXTURE_SIZE * texture_y + wall->texture_x];
		if (game->last_hit_side == 1)
			color = (color >> 1) & 8355711; // Darken colors for y-side walls
		game->buffer[y][pixel] = color;
		y++;
	}
}

void	draw_wall(t_dda *ray, t_cub3d *game, int pixel)
{
	t_wall_slice	wall;

	game->texture = set_wall(game, ray);
	wall.height = (HEIGHT / ray->perp_dist);
	wall.line_start_y = (HEIGHT / 2 - wall.height / 2);
	wall.line_end_y = (HEIGHT / 2 + wall.height / 2);
	if (wall.line_start_y < 0)
		wall.line_start_y = 0;
	if (wall.line_end_y >= HEIGHT)
		wall.line_end_y = HEIGHT - 1;
	intersection_point(ray, game, &wall);
	find_texture_position_x(ray, game, &wall);
	wall.texture_pos = (wall.line_start_y - HEIGHT / 2 + wall.height / 2)
		* wall.texture_step;
	render_wall(game, pixel, &wall);
}
