/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:25:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/13 13:45:07 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

double	*intersect_cylinder_body(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	*quad;

	oc_vector = substract_tuple(ray->origin, obj->cords);
	if (!oc_vector)
		return (NULL);
	quad = init_cylinder_quad(obj, ray, oc_vector);
	arr_t = calculate_intersection_points(obj, ray, oc_vector, quad);
	free(oc_vector);
	if (quad)
		free(quad);
	if (arr_t && arr_t[0] == INFINITY && arr_t[1] == INFINITY)
	{
		printf("Object does not intersect");
		free(arr_t);
		return (NULL);
	}
	return (arr_t);
}

static double	intersect_cap(t_object *obj, t_ray *ray, double *center,
		double direction)
{
	double	t;
	double	*hit_point;
	double	*center_to_hit;
	double	dist_squared;
	double	*obj_vector;

	obj_vector = multiply_tuple(obj->vector, direction);
	if (compare_floats(dot(ray->direction, obj_vector), 0.0))
		return (free(obj_vector), INFINITY);
	t = dot(substract_tuple(center, ray->origin), obj->vector) * direction
		/ dot(ray->direction, obj_vector);
	free(obj_vector);
	if (t <= 0)
		return (INFINITY);
	hit_point = add_tuple(ray->origin, multiply_tuple(ray->direction, t));
	center_to_hit = substract_tuple(hit_point, center);
	dist_squared = dot(center_to_hit, center_to_hit) - pow(dot(center_to_hit,
				obj->vector), 2);
	free(hit_point);
	free(center_to_hit);
	if (dist_squared > pow(obj->diameter / 2, 2))
		return (INFINITY);
	return (t);
}

double	*intersect_cylinder_caps(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	t_bottom;
	double	t_top;
	double	*top_center;
	double	*v_h;

	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	t_bottom = intersect_cap(obj, ray, obj->cords, -1.0);
	v_h = multiply_tuple(obj->vector, obj->height);
	top_center = add_tuple(obj->cords, v_h);
	free(v_h);
	t_top = intersect_cap(obj, ray, top_center, 1.0);
	free(top_center);
	arr_t[0] = t_bottom;
	arr_t[1] = t_top;
	if (t_bottom == INFINITY && t_top == INFINITY)
	{
		free(arr_t);
		return (NULL);
	}
	return (arr_t);
}

double	*prepare_intersection_result(double t1, double t2)
{
	double	*result_t;
	double	tmp;

	if (t1 == INFINITY && t2 == INFINITY)
		return (NULL);
	result_t = init_result_t();
	if (!result_t)
		return (NULL);
	if (t1 > t2)
	{
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	result_t[0] = t1;
	result_t[1] = t2;
	return (result_t);
}

double	*intersect_cylinder(t_object *obj, t_ray *ray)
{
	double	*side_t;
	double	*caps_t;
	double	*result_t;
	double	t1;
	double	t2;

	side_t = intersect_cylinder_body(obj, ray);
	caps_t = intersect_cylinder_caps(obj, ray);
	if (!side_t && !caps_t)
		return (NULL);
	result_t = init_result_t();
	if (!result_t)
	{
		clean_intersect_memory(side_t, caps_t);
		return (NULL);
	}
	t1 = INFINITY;
	t2 = INFINITY;
	find_closest_t(side_t, caps_t, &t1, &t2);
	clean_intersect_memory(side_t, caps_t);
	free(result_t);
	return (prepare_intersection_result(t1, t2));
}
