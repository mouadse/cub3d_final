/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:44:35 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:39:48 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Replaced exit() with handle_error() in init_image
#include "cub3d.h"

uint32_t	tex_pixel(t_tex *t, int x, int y)
{
	char	*p;

	if (x < 0 || x >= t->w || y < 0 || y >= t->h)
		return (0);
	p = t->addr + (y * t->line_len + x * (t->bpp / 8));
	return (*(uint32_t *)p);
}

void	init_image(t_cub3d *g, int w, int h)
{
	g->img.ptr = mlx_new_image(g->mlx, w, h);
	if (!g->img.ptr)
	{
		handle_error("Error: mlx_new_image() failed in init_image\n", g);
	}
	g->img.addr = mlx_get_data_addr(g->img.ptr, &g->img.bpp, &g->img.line_len,
			&g->img.endian);
	g->img.w = w;
	g->img.h = h;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, uint32_t col)
{
	char	*dst;

	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(uint32_t *)dst = col;
}
