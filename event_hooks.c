/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:10:19 by msennane          #+#    #+#             */
/*   Updated: 2025/05/06 16:34:40 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_cub3d *game)
{
	if (keycode == KEY_ESC)
	{
		// Handle exit event
	}
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
