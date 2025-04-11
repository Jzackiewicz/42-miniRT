/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:56:01 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 13:23:13 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_checker_p	init_checker_pattern(int color_a, int color_b)
{
	t_checker_p	res;

	res.color_a = color_a;
	res.color_b = color_b;
	res.transform = init_matrix(4, 4);
	if (!res.transform)
		return (res);
	make_identity(res.transform);
	return (res);
}

/*
	determines the color at the given point in the checker pattern
	returns color_a if the sum of floor(x) + floor(y) + floor(z) is even,
	otherwise returns color_b
 */
int	checker_at(t_checker_p pattern, double *point)
{
	int	sum;

	if (!point)
		return (0);
	sum = (int)floor(point[0]) + (int)floor(point[1]) + (int)floor(point[2]);
	if (0 == (sum % 2))
		return (pattern.color_a);
	else
		return (pattern.color_b);
}

/*
	Determines the color at a point on an object, considering both
	the object's transformation and the pattern's transformation
 */
int	checker_at_object(t_object *object, double *world_point)
{
	int		color;
	double *obj_point;
	double *pattern_point;
	t_checker_p pattern;

	pattern = init_checker_pattern(0x0000FF, 0xFF0000);
	if (!pattern.transform)
		return (0);
	obj_point = multiply_tuple_and_matrix(inverse(object->transform),
	world_point);
	if (!obj_point)
		return (0);
	pattern_point = multiply_tuple_and_matrix(inverse(pattern.transform),
			obj_point);
	if (!pattern_point)
	{
		free(obj_point);
		return (0);
	}
	color = checker_at(pattern, pattern_point);
	free(obj_point);
	free(pattern_point);
	free(pattern.transform);
	return (color);
}