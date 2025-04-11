/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:56:01 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 14:22:20 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

// TODO: dynamic checker sizing according to distance

void	set_pattern_transform(t_checker_p *pattern, t_matrix *transform)
{
	if (pattern->transform)
		free(pattern->transform);
	pattern->transform = transform;
	pattern->inv_transform = inverse(transform);
}

t_checker_p	init_checker_pattern(t_object *obj)
{
	t_checker_p	res;

	res.color_a = rgb_to_int(obj->color);
	res.color_b = 0xFFFFFF - rgb_to_int(obj->color);
	res.transform = init_matrix(4, 4);
	if (!res.transform)
		return (res);
	make_identity(res.transform);
	res.inv_transform = init_matrix(4, 4);
	if (!res.inv_transform)
	{
		free(res.transform);
		res.transform = NULL;
		return (res);
	}
	make_identity(res.inv_transform);
	return (res);
}

/*
	determines the color at the given point in the checker pattern
	returns color_a if the sum of floor(x) + floor(y) + floor(z) is even,
	otherwise returns color_b
 */
int	checker_at(t_checker_p pattern, double *point)
{
	int sum;

	if (!point)
		return (0);
	double x = point[0] * 0.6;
	double y = point[1] * 0.6;	
	double z = point[2] * 0.6; 
	
	sum = (int)floor(x + EPSILON) + (int)floor(y + EPSILON) + (int)floor(z + EPSILON);
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
	int			color;
	double		*obj_point;
	double		*pattern_point;
	t_checker_p	pattern;

	pattern = init_checker_pattern(object);
	if (!pattern.transform || !pattern.inv_transform)
		return (0);
	obj_point = multiply_tuple_and_matrix(object->inv_transform, world_point);
	if (!obj_point)
		return (0);
	pattern_point = multiply_tuple_and_matrix(pattern.inv_transform, obj_point);
	if (!pattern_point)
	{
		free(obj_point);
		return (0);
	}
	color = checker_at(pattern, pattern_point);
	free(obj_point);
	free(pattern_point);
	free(pattern.transform);
	free(pattern.inv_transform);
	return (color);
}

