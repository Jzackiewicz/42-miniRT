/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:38:59 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/13 13:14:30 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

double	check_height_constraints(t_object *obj, t_ray *ray, double *oc_vector,
		double t)
{
	double	m;

	m = dot(oc_vector, obj->vector) + t * dot(ray->direction, obj->vector);
	if (m < 0 || m > obj->height)
		return (INFINITY);
	return (t);
}

int	check_cylinder_discriminant(double *quad, double **arr_t, double *oc_vector)
{
	double	delta;

	if (!quad || compare_floats(quad[0], 0.0))
	{
		printf("Object does not intersect");
		free_cylinder_resources(*arr_t, oc_vector, quad);
		*arr_t = NULL;
		return (0);
	}
	delta = pow(quad[1], 2) - 4 * quad[0] * quad[2];
	if (delta < 0)
	{
		free_cylinder_resources(*arr_t, oc_vector, quad);
		*arr_t = NULL;
		return (0);
	}
	return (1);
}

double	*calculate_intersection_points(t_object *obj, t_ray *ray,
		double *oc_vector, double *quad)
{
	double	*arr_t;
	double	t1;
	double	t2;

	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	if (!check_cylinder_discriminant(quad, &arr_t, oc_vector))
		return (NULL);
	t1 = (-quad[1] - sqrt(pow(quad[1], 2) - 4 * quad[0] * quad[2])) / (2
			* quad[0]);
	t2 = (-quad[1] + sqrt(pow(quad[1], 2) - 4 * quad[0] * quad[2])) / (2
			* quad[0]);
	t1 = check_height_constraints(obj, ray, oc_vector, t1);
	t2 = check_height_constraints(obj, ray, oc_vector, t2);
	arr_t[0] = t1;
	arr_t[1] = t2;
	return (arr_t);
}

void	find_closest_t(double *side_t, double *caps_t, double *t1, double *t2)
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
