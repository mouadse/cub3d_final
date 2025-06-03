/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2025/06/02 20:41:05 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>  // For printf (mainly for error messages to stderr)
// TODO: Replaced get_game() with direct &game pointer in main.c
#include <stdlib.h> // For exit, EXIT_FAILURE
#include <string.h> // For memset

int	main(int argc, char **argv)
{
	t_cub3d		game;
	t_config	config;

	memset(&game, 0, sizeof(t_cub3d));
	memset(&config, 0, sizeof(t_config));
	game.config = &config;
	game.exit_requested = false;
	validate_map(argc, argv, &game);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		fprintf(stderr, "Error: mlx_init() failed\n");
		free_memory(&game);
		return (EXIT_FAILURE);
	}
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game.win)
	{
		fprintf(stderr, "Error: mlx_new_window() failed\n");
		free_memory(&game);
		return (EXIT_FAILURE);
	}
	init_image(&game, SCREEN_WIDTH, SCREEN_HEIGHT);
	set_player_position_and_plane(&game);
	memset(&game.keys, 0, sizeof(game.keys));
	load_textures(&game);
	draw_background2(&game);
	draw_rays(&game);
	mlx_put_image_to_window(game.mlx, game.win,
		game.img.ptr, 0, 0);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
