/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:56:09 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:39:07 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sign_of(float v)
{
	if (v < 0.0f)
		return (-1);
	else
		return (1);
}

t_vec2	calc_delta_dist(t_vec2 dir)
{
	t_vec2	delta;

	if (dir.x == 0.0f)
		delta.x = INFINITY;
	else
		delta.x = fabsf(1.0f / dir.x);
	if (dir.y == 0.0f)
		delta.y = INFINITY;
	else
		delta.y = fabsf(1.0f / dir.y);
	return (delta);
}

void	init_side_dist(t_dda *ray, t_vec2 pos)
{
	ray->map.x = (int)pos.x;
	ray->map.y = (int)pos.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist_side.x = (pos.x - (float)ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->dist_side.x = ((float)ray->map.x + 1.0f - pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist_side.y = (pos.y - (float)ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist_side.y = ((float)ray->map.y + 1.0f - pos.y)
			* ray->delta_dist.y;
	}
}
