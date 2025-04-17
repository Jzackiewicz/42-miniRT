/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:56:01 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/17 18:05:48 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/*	Check whether color ofparticular point at object is supposed to
	be inverted or not */
static bool	is_color_inverted_at(t_object *obj, double *point)
{
	double	scale;
	int		sum;
	int		i;

	if (0 == ft_strncmp(obj->id, "sp\0", 3))
		scale = SPHERE_CHECKER_SCALE;
	else if (0 == ft_strncmp(obj->id, "pl\0", 3))
		scale = PLANE_CHECKER_SCALE;
	else if (0 == ft_strncmp(obj->id, "cy\0", 3))
		scale = CYLINDER_CHECKER_SCALE;
	i = -1;
	while (++i < 3)
		point[i] = point[i] * scale;
	sum = (int)floor(point[0] + EPSILON) + (int)floor(point[1] + EPSILON)
		+ (int)floor(point[2] + EPSILON);
	if (0 == (sum % 2))
		return (false);
	else
		return (true);
}

static double	*invert_color(double *old_color)
{
	double	*new_color;

	new_color = tupledup(old_color, 3);
	new_color[0] = 255 - old_color[0];
	new_color[1] = 255 - old_color[1];
	new_color[2] = 255 - old_color[2];
	return (new_color);
}

double	*get_checkered_color(t_object *obj, double *point)
{
	double	*color;
	double	*obj_point;

	obj_point = multiply_tuple_and_matrix(obj->inv_transform, point);
	if (!obj_point)
		return (NULL);
	if (is_color_inverted_at(obj, obj_point))
		color = invert_color(obj->color);
	else
		color = tupledup(obj->color, 3);
	free(obj_point);
	return (color);
}
