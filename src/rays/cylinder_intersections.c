/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:25:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/12 17:52:18 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

double	*scale_tuple(double *vector, double scalar)
{
	double	*result;

	result = (double *)malloc(sizeof(double) * 3);
	if (!result)
		return (NULL);
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
	result[2] = vector[2] * scalar;
	return (result);
}

double	*init_cylinder_quad(t_object *obj, t_ray *ray, double *oc_vector)
{
	double	*quad;

	quad = (double *)malloc(sizeof(double) * 3);
	if (!quad)
		return (NULL);
	quad[0] = dot(ray->direction, ray->direction) - pow(dot(ray->direction,
				obj->vector), 2);
	quad[1] = 2 * (dot(ray->direction, oc_vector) - dot(ray->direction,
				obj->vector) * dot(oc_vector, obj->vector));
	quad[2] = dot(oc_vector, oc_vector) - pow(dot(oc_vector, obj->vector), 2)
		- pow(obj->diameter / 2, 2);
	return (quad);
}

static double	check_height_constraints(t_object *obj, t_ray *ray,
		double *oc_vector, double t)
{
	double	m;

	m = dot(oc_vector, obj->vector) + t * dot(ray->direction, obj->vector);
	if (m < 0 || m > obj->height)
		return (INFINITY);
	return (t);
}

double	*intersect_cylinder_body(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	*quad;
	double	delta;
	double	t1;
	double	t2;

	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	oc_vector = substract_tuple(ray->origin, obj->cords);
	quad = init_cylinder_quad(obj, ray, oc_vector);
	if (!quad || compare_floats(quad[0], 0.0, 1e-6))
	{
		printf("Object does not intersect");
		free(arr_t);
		free(oc_vector);
		if (quad)
			free(quad);
		return (NULL);
	}
	delta = pow(quad[1], 2) - 4 * quad[0] * quad[2];
	if (delta < 0)
	{
		printf("Object does not intersect");
		free(arr_t);
		free(oc_vector);
		free(quad);
		return (NULL);
	}
	t1 = (-quad[1] - sqrt(delta)) / (2 * quad[0]);
	t2 = (-quad[1] + sqrt(delta)) / (2 * quad[0]);
	t1 = check_height_constraints(obj, ray, oc_vector, t1);
	t2 = check_height_constraints(obj, ray, oc_vector, t2);
	free(oc_vector);
	free(quad);
	arr_t[0] = t1;
	arr_t[1] = t2;
	if (t1 == INFINITY && t2 == INFINITY)
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
	double	denom;
	double	t;
	double	*hit_point;
	double	*center_to_hit;
	double	dist_squared;
	double	*obj_vector;

	obj_vector = scale_tuple(obj->vector, direction);
	denom = dot(ray->direction, obj_vector);
	free(obj_vector);
	if (compare_floats(denom, 0.0, 1e-6))
		return (INFINITY);
	t = dot(substract_tuple(center, ray->origin), obj->vector) * direction
		/ denom;
	if (t <= 0)
		return (INFINITY);
	hit_point = add_tuple(ray->origin, scale_tuple(ray->direction, t));
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

	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	t_bottom = intersect_cap(obj, ray, obj->cords, -1.0);
	top_center = add_tuple(obj->cords, scale_tuple(obj->vector, obj->height));
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

static void	find_closest_t(double *side_t, double *caps_t, double *t1,
		double *t2)
{
	if (side_t)
	{
		if (side_t[0] > 0 && side_t[0] < *t1)
			*t1 = side_t[0];
		if (side_t[1] > 0 && side_t[1] < *t2)
			*t2 = side_t[1];
	}
	if (caps_t)
	{
		if (caps_t[0] > 0 && caps_t[0] < *t1)
			*t1 = caps_t[0];
		if (caps_t[1] > 0 && caps_t[1] < *t2)
			*t2 = caps_t[1];
	}
}

double	*intersect_cylinder(t_object *obj, t_ray *ray)
{
	double	*side_t;
	double	*caps_t;
	double	*result_t;
	double	t1;
	double	t2;
	double	tmp;

	side_t = intersect_cylinder_body(obj, ray);
	caps_t = intersect_cylinder_caps(obj, ray);
	if (!side_t && !caps_t)
		return (NULL);
	result_t = (double *)malloc(sizeof(double) * 2);
	if (!result_t)
	{
		if (side_t)
			free(side_t);
		if (caps_t)
			free(caps_t);
		return (NULL);
	}
	t1 = INFINITY;
	t2 = INFINITY;
	find_closest_t(side_t, caps_t, &t1, &t2);
	if (side_t)
		free(side_t);
	if (caps_t)
		free(caps_t);
	if (t1 == INFINITY && t2 == INFINITY)
	{
		free(result_t);
		return (NULL);
	}
	if (t1 > t2)
	{
		tmp = t2;
		t2 = t1;
		t1 = tmp;
	}
	result_t[0] = t1;
	result_t[1] = t2;
	return (result_t);
}
