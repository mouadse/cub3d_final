/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:25 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 12:25:22 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	rotate_vector(t_vec2 vector, float angle_degrees)
{
	t_vec2	rotated_vector;
	float	angle_radians;

	angle_radians = angle_degrees * (PI / 180.0f);
	rotated_vector.x = vector.x * cosf(angle_radians) - vector.y
		* sinf(angle_radians);
	rotated_vector.y = vector.x * sinf(angle_radians) + vector.y
		* cosf(angle_radians);
	return (rotated_vector);
}
