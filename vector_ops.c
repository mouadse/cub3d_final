/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:25 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 12:25:38 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
