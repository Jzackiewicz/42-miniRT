/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:56:01 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 16:02:14 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static t_checker_p	init_checker_pattern(t_object *obj)
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

	EPSILON is utilized to avoid floating
	point errors and increase floating point precision
 */
static int	checker_at(t_object *obj, t_checker_p pattern, double *point)
{
	int		sum;
	int		i;
	double	*xyz;
	double	scale;

	if (!point)
		return (0);
	xyz = malloc(3 * sizeof(double));
	if (!xyz)
		return (0);
	if (0 == ft_strncmp(obj->id, "sp\0", 3))
		scale = SPHERE_CHECKER_SCALE;
	else if (0 == ft_strncmp(obj->id, "pl\0", 3))
		scale = PLANE_CHECKER_SCALE;
	else if (0 == ft_strncmp(obj->id, "cy\0", 3))
		scale = CYLINDER_CHECKER_SCALE;
	i = -1;
	while (++i < 3)
		xyz[i] = point[i] * scale;
	sum = (int)floor(xyz[0] + EPSILON) + (int)floor(xyz[1] + EPSILON)
		+ (int)floor(xyz[2] + EPSILON);
	if (0 == (sum % 2))
		return (free(xyz), pattern.color_a);
	else
		return (free(xyz), pattern.color_b);
}

static void	free_pattern_components(double *obj_point, double *pattern_point,
		t_checker_p pattern)
{
	free(obj_point);
	free(pattern_point);
	free(pattern.transform);
	free(pattern.inv_transform);
}

static double	*split_color(int checker_color, double *res)
{
	res[0] = ((checker_color >> 16) & 0xFF);
	res[1] = ((checker_color >> 8) & 0xFF);
	res[2] = (checker_color & 0xFF);
	return (res);
}

/*
	determines the color at a point on an object, considering both
	the object's transformation and the pattern's transformation
	returns a color split to RGB channels to apply in the phong model
 */
double	*checker_at_object(t_object *object, double *world_point)
{
	double		*res;
	double		*obj_point;
	double		*pattern_point;
	t_checker_p	pattern;
	int			checker_color;

	pattern = init_checker_pattern(object);
	if (!pattern.transform || !pattern.inv_transform)
		return (NULL);
	obj_point = multiply_tuple_and_matrix(object->inv_transform, world_point);
	if (!obj_point)
		return (NULL);
	pattern_point = multiply_tuple_and_matrix(pattern.inv_transform, obj_point);
	if (!pattern_point)
		return (free(obj_point), NULL);
	checker_color = checker_at(object, pattern, pattern_point);
	res = malloc(3 * sizeof(double));
	if (!res)
	{
		free_pattern_components(obj_point, pattern_point, pattern);
		return (NULL);
	}
	res = split_color(checker_color, res);
	free_pattern_components(obj_point, pattern_point, pattern);
	return (res);
}

double	*get_checker_color(t_comps *comps)
{
	double	*new_color;

	if (true == comps->obj->is_checkered)
        new_color = checker_at_object(comps->obj, comps->point);
	else
		new_color = tupledup(comps->obj->color, 3);
	return(new_color);
}
