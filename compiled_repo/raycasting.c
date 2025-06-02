/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:04:35 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:38:51 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static int	is_wall(char **map, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (1);
	return (map[y][x] == '1');
}

void	perform_dda(t_dda *ray, char **map, int *hit_side)
{
	while (1)
	{
		if (is_wall(map, ray->map.x, ray->map.y))
			break ;
		if (ray->dist_side.x < ray->dist_side.y)
		{
			ray->dist_side.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->hit_side = 0;
			*hit_side = 0;
		}
		else
		{
			ray->dist_side.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->hit_side = 1;
			*hit_side = 1;
		}
	}
	if (ray->hit_side == 0)
		ray->perp_dist = (ray->dist_side.x - ray->delta_dist.x);
	else
		ray->perp_dist = (ray->dist_side.y - ray->delta_dist.y);
}

void	draw_rays(t_cub3d *game)
{
	t_dda	ray;
	memset(&ray, 0, sizeof(t_dda));
	int		pixel;

	pixel = 0;
	while (pixel < SCREEN_WIDTH)
	{
		ray.plane_multiplier = 2.0f * pixel / (float)SCREEN_WIDTH - 1.0f;
		ray.camera_pixel = vector_multiply(game->camera_plane, ray.plane_multiplier);
		ray.dir = vector_add(game->player_dir, ray.camera_pixel);
		ray.map.x = (int)game->player_pos.x;
		ray.map.y = (int)game->player_pos.y;
		ray.delta_dist = calc_delta_dist(ray.dir);
		init_side_dist(&ray, game->player_pos);
		perform_dda(&ray, game->config->grid, &game->last_hit_side);
		draw_wall(&ray, game, pixel);
		pixel++;
	}
}
