/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:53:28 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:44:37 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	init_player_camera(t_cub3d *game)
{
	char orientation;

	orientation = game->config->character_orientation;
	if (orientation == 'N')
	{
		game->player_dir = create_vector(0.0f, -1.0f);
		game->camera_plane = create_vector(0.66f, 0.0f);
	}
	else if (orientation == 'S')
	{
		game->player_dir = create_vector(0.0f, 1.0f);
		game->camera_plane = create_vector(-0.66f, 0.0f);
	}
	else if (orientation == 'W')
	{
		game->player_dir = create_vector(-1.0f, 0.0f);
		game->camera_plane = create_vector(0.0f, -0.66f);
	}
	else if (orientation == 'E')
	{
		game->player_dir = create_vector(1.0f, 0.0f);
		game->camera_plane = create_vector(0.0f, 0.66f);
	}
}

void	set_player_position_and_plane(t_cub3d *game)
{
	game->player_pos = create_vector(
		(float)game->config->character_pos_x + 0.5f,
		(float)game->config->character_pos_y + 0.5f
		);

	init_player_camera(game);
}
