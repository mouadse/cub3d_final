/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:06:49 by msennane          #+#    #+#             */
/*   Updated: 2025/06/04 19:50:58 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	*get_wall_texture(t_cub3d *game, t_dda *ray)
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
}

void	intersection_point(t_dda *ray, t_cub3d *game, t_wall_slice *wall)
{
	if (ray->hit_side == 0)
		wall->hit_pos_x = game->player_pos.y + ray->perp_dist * ray->dir.y;
	else
		wall->hit_pos_x = game->player_pos.x + ray->perp_dist * ray->dir.x;
	wall->hit_pos_x -= floorf(wall->hit_pos_x);
	if (wall->slice_height == 0)
		wall->tex_step = 0;
	else
		wall->tex_step = 1.0f * game->texture->h / (float)wall->slice_height;
}

void	find_texture_position_x(t_dda *ray, t_cub3d *game, t_wall_slice *wall)
{
	wall->tex_x = (int)(wall->hit_pos_x * (float)game->texture->w);
	if ((ray->hit_side == 0 && ray->dir.x > 0))
		wall->tex_x = game->texture->w - wall->tex_x - 1;
	if ((ray->hit_side == 1 && ray->dir.y < 0))
		wall->tex_x = game->texture->w - wall->tex_x - 1;
}

static void	render_wall(t_cub3d *game, int pixel, t_wall_slice *wall)
{
	int			current_screen_y;
	int			texture_y_coord;
	uint32_t	pixel_color;

	current_screen_y = wall->draw_start_y;
	while (current_screen_y < wall->draw_end_y)
	{
		texture_y_coord = (int)wall->tex_pos;
		if (texture_y_coord < 0)
			texture_y_coord = 0;
		if (texture_y_coord >= game->texture->h)
			texture_y_coord = game->texture->h - 1;
		wall->tex_pos += wall->tex_step;
		pixel_color = tex_pixel(game->texture, wall->tex_x, texture_y_coord);
		my_mlx_pixel_put(&game->img, pixel, current_screen_y, pixel_color);
		current_screen_y++;
	}
}

void	draw_wall(t_dda *ray, t_cub3d *game, int pixel)
{
	t_wall_slice	wall;
	float			safe_dist;

	safe_dist = ray->perp_dist;
	if (safe_dist < 0.0001f)
		safe_dist = 0.0001f;
	game->texture = get_wall_texture(game, ray);
	if (!game->texture || !game->texture->ptr)
		return ;
	wall.slice_height = (int)((float)SCREEN_HEIGHT / safe_dist);
	wall.draw_start_y = SCREEN_HEIGHT / 2 - wall.slice_height / 2;
	wall.draw_end_y = SCREEN_HEIGHT / 2 + wall.slice_height / 2;
	if (wall.draw_start_y < 0)
		wall.draw_start_y = 0;
	if (wall.draw_end_y >= SCREEN_HEIGHT)
		wall.draw_end_y = SCREEN_HEIGHT - 1;
	intersection_point(ray, game, &wall);
	find_texture_position_x(ray, game, &wall);
	wall.tex_pos = ((float)wall.draw_start_y - (float)SCREEN_HEIGHT / 2.0f
			+ (float)wall.slice_height / 2.0f) * wall.tex_step;
	render_wall(game, pixel, &wall);
}
