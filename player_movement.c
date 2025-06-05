/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:37:02 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 13:33:27 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_walkable(t_cub3d *game, float x, float y)
{
	const float	collision_margin = 0.1f;

	if (game->config->grid[(int)(y + collision_margin * sign_of(y
				- game->player_pos.y))][(int)x] == '1')
		return (false);
	if (game->config->grid[(int)y][(int)(x + collision_margin * sign_of(x
			- game->player_pos.x))] == '1')
		return (false);
	if (game->config->grid[(int)(y + collision_margin
			* sign_of(game->camera_plane.y))][(int)x] == '1')
		return (false);
	if (game->config->grid[(int)y][(int)(x + collision_margin
		* sign_of(game->camera_plane.x))] == '1')
		return (false);
	return (true);
}

static void	compute_target_position(t_cub3d *game, float *out_x, float *out_y)
{
	float	move_speed;

	move_speed = game->frame_time * 4.0f;
	*out_x = game->player_pos.x;
	*out_y = game->player_pos.y;
	if (game->keys.w)
	{
		*out_x += game->player_dir.x * move_speed;
		*out_y += game->player_dir.y * move_speed;
	}
	if (game->keys.s)
	{
		*out_x -= game->player_dir.x * move_speed;
		*out_y -= game->player_dir.y * move_speed;
	}
	if (game->keys.a)
	{
		*out_x -= game->camera_plane.x * move_speed;
		*out_y -= game->camera_plane.y * move_speed;
	}
	if (game->keys.d)
	{
		*out_x += game->camera_plane.x * move_speed;
		*out_y += game->camera_plane.y * move_speed;
	}
}

static void	prepare_movement_params(t_cub3d *game, float *target_x,
		float *target_y, float *rotation_speed)
{
	game->lerp_factor = 1.0f;
	*rotation_speed = game->frame_time * 40.5f;
	compute_target_position(game, target_x, target_y);
}

void	update_player_movement(t_cub3d *game)
{
	float	target_x;
	float	target_y;
	float	rotation_speed;

	prepare_movement_params(game, &target_x, &target_y, &rotation_speed);
	if (is_walkable(game, target_x, game->player_pos.y))
	{
		game->player_pos.x += game->lerp_factor * (target_x
				- game->player_pos.x);
	}
	if (is_walkable(game, game->player_pos.x, target_y))
	{
		game->player_pos.y += game->lerp_factor * (target_y
				- game->player_pos.y);
	}
	if (game->keys.left)
	{
		game->player_dir = rotate_vector(game->player_dir, -rotation_speed);
		game->camera_plane = rotate_vector(game->camera_plane, -rotation_speed);
	}
	if (game->keys.right)
	{
		game->player_dir = rotate_vector(game->player_dir, rotation_speed);
		game->camera_plane = rotate_vector(game->camera_plane, rotation_speed);
	}
}
