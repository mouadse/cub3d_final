/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:10:19 by msennane          #+#    #+#             */
/*   Updated: 2025/06/04 19:46:41 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	key_press(int keycode, t_cub3d *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		game->keys.w = true;
	else if (keycode == KEY_S)
		game->keys.s = true;
	else if (keycode == KEY_A)
		game->keys.a = true;
	else if (keycode == KEY_D)
		game->keys.d = true;
	else if (keycode == KEY_LEFTAR)
		game->keys.left = true;
	else if (keycode == KEY_RIGHTAR)
		game->keys.right = true;
	return (0);
}

int	key_release(int keycode, t_cub3d *game)
{
	if (keycode == KEY_W)
		game->keys.w = false;
	else if (keycode == KEY_S)
		game->keys.s = false;
	else if (keycode == KEY_A)
		game->keys.a = false;
	else if (keycode == KEY_D)
		game->keys.d = false;
	else if (keycode == KEY_LEFTAR)
		game->keys.left = false;
	else if (keycode == KEY_RIGHTAR)
		game->keys.right = false;
	return (0);
}

int	close_window(t_cub3d *game)
{
	if (game)
		game->exit_requested = true;
	return (0);
}

int	game_loop(t_cub3d *game)
{
	if (game->exit_requested)
	{
		free_memory(game);
		exit(0);
	}
	game->frame_time = FIXED_FRAME_TIME;
	update_player_movement(game);
	draw_background2(game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}
