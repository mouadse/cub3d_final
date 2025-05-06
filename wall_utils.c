/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:06:49 by msennane          #+#    #+#             */
/*   Updated: 2025/05/06 16:06:54 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	select_texture(t_cub3d *game, t_dda *ray)
{
	if (ray->hit_side == 0)
	{
		if (ray->step.x < 0)
			return (0);
		return (1);
	}
	else
	{
		if (ray->step.y < 0)
			return (2);
		return (3);
	}
}

void	intersection_point(t_dda *ray, t_cub3d *game, t_wall_slice *wall)
{
	if (ray->hit_side == 0)
		wall->hit_pos_x = game->player_pos.y + ray->perp_dist * ray->dir.y;
	else
		wall->hit_pos_x = game->player_pos.x + ray->perp_dist * ray->dir.x;
	wall->hit_pos_x -= floor(wall->hit_pos_x);
	wall->tex_step = 1.0 * TEX_HEIGHT / wall->slice_height;
}

void	find_texture_position_x(t_dda *ray, t_cub3d *game, t_wall_slice *wall)
{
	int	texture_id;

	texture_id = select_texture(game, ray);
	wall->tex_x = (int)(wall->hit_pos_x * TEX_WIDTH);
	if ((ray->hit_side == 0 && ray->dir.x > 0) || (ray->hit_side == 1
			&& ray->dir.y < 0))
		wall->tex_x = TEX_WIDTH - wall->tex_x - 1;
	game->last_hit_side = ray->hit_side;
}

void	render_wall(t_cub3d *game, int pixel, t_wall_slice *wall)
{
	int	y;
	int	color;
	int	texture_y;
	int	texture_id;

	texture_id = select_texture(game, NULL);
	y = wall->draw_start_y;
	while (y < wall->draw_end_y)
	{
		texture_y = (int)wall->tex_pos & (TEX_HEIGHT - 1);
		wall->tex_pos += wall->tex_step;
		color = game->texture_pixels[texture_id][TEX_WIDTH * texture_y
			+ wall->tex_x];
		if (game->last_hit_side == 1)
			color = (color >> 1) & 8355711;
		mlx_pixel_put(game->mlx_ptr, game->window_ptr, pixel, y, color);
		y++;
	}
}

void	draw_wall(t_dda *ray, t_cub3d *game, int pixel)
{
	t_wall_slice	wall;

	wall.slice_height = (int)(SCREEN_HEIGHT / ray->perp_dist);
	wall.draw_start_y = (SCREEN_HEIGHT / 2 - wall.slice_height / 2);
	wall.draw_end_y = (SCREEN_HEIGHT / 2 + wall.slice_height / 2);
	if (wall.draw_start_y < 0)
		wall.draw_start_y = 0;
	if (wall.draw_end_y >= SCREEN_HEIGHT)
		wall.draw_end_y = SCREEN_HEIGHT - 1;
	intersection_point(ray, game, &wall);
	find_texture_position_x(ray, game, &wall);
	wall.tex_pos = (wall.draw_start_y - (int)((float)SCREEN_HEIGHT / 2)
			+ (int)((float)wall.slice_height / 2)) * wall.tex_step;
	render_wall(game, pixel, &wall);
}
