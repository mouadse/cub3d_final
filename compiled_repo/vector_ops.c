/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:25 by msennane          #+#    #+#             */
/*   Updated: 2025/06/02 20:35:54 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h" // Includes math.h for sqrt, cos, sin, M_PI if defined
t_vec2	create_vector(float x, float y)
{
	t_vec2	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	return (new_vector);
}

t_vec2	vector_add(t_vec2 a, t_vec2 b)
{
	t_vec2	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec2	vector_subtract(t_vec2 a, t_vec2 b)
{
	t_vec2	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_vec2	vector_multiply(t_vec2 a, float scalar)
{
	t_vec2	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return (result);
}

float	vector_magnitude(t_vec2 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y));
}

t_vec2	rotate_vector(t_vec2 vector, float angle_degrees)
{
	t_vec2	rotated_vector;
	float	angle_radians;

	angle_radians = angle_degrees * (PI / 180.0f);
	rotated_vector.x = vector.x * cosf(angle_radians) - vector.y * sinf(angle_radians);
	rotated_vector.y = vector.x * sinf(angle_radians) + vector.y * cosf(angle_radians);

	return (rotated_vector);
}
