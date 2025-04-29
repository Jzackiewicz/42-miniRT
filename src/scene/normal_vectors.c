/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:42:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/29 16:14:08 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static double	*get_sphere_normal_at(t_object *obj, double *w_point)
{
	double	*sphere_center;
	double	*obj_normal;
	double	*obj_point;
	double	*world_normal;

	sphere_center = init_tuple(0, 0, 0, 1);
	obj_point = multiply_tuple_and_matrix(obj->inv_transform, w_point);
	obj_normal = subtract_tuple(obj_point, sphere_center);
	free(obj_point);
	normalize(&obj_normal);
	transpose(&obj->inv_transform);
	world_normal = multiply_tuple_and_matrix(obj->inv_transform, obj_normal);
	transpose(&obj->inv_transform);
	normalize(&world_normal);
	free(sphere_center);
	free(obj_normal);
	return (world_normal);
}

double	*get_cylinder_normal_at(t_object *obj, double *w_point)
{
	double	distance;
	double	*obj_point;
	double	*obj_normal;
	double	*world_normal;
	
	obj_point = multiply_tuple_and_matrix(obj->inv_transform, w_point);
	distance = pow(obj_point[0], 2) + pow(obj_point[2], 2);
	obj_normal = init_tuple(0, 0, 0, 0);
	if (distance < 1.0 && (obj_point[1] > 0.5 - EPSILON
			|| compare_floats(obj_point[1], 0.5)))
		obj_normal[1] = 1;
	else if (distance < 1.0 && (obj_point[1] < -0.5 + EPSILON
			|| compare_floats(obj_point[1], -0.5)))
		obj_normal[1] = -1;
	else
	{
		obj_normal[0] = obj_point[0];
		obj_normal[2] = obj_point[2];
	}
	free(obj_point);
	transpose(&obj->inv_transform);
	world_normal = multiply_tuple_and_matrix(obj->inv_transform, obj_normal);
	transpose(&obj->inv_transform);
	normalize(&world_normal);
	return (world_normal, free(obj_normal));
}

static double	*get_cone_normal_at(t_object *obj, double *w_point)
{
	double	distance;
	double	*obj_point;
	double	*obj_normal;
	double	*world_normal;

	obj_point = multiply_tuple_and_matrix(obj->inv_transform, w_point);
	distance = pow(obj_point[0], 2) + pow(obj_point[2], 2);
	obj_normal = init_tuple(0, 0, 0, 0);
	if (distance < 1.0 && compare_floats(obj_point[1], -0.5))
		obj_normal[1] = -1;
	else
	{
		obj_normal[0] = obj_point[0];
		obj_normal[1] = sqrt(distance);
		obj_normal[2] = obj_point[2];
	}
	free(obj_point);
	transpose(&obj->inv_transform);
	world_normal = multiply_tuple_and_matrix(obj->inv_transform, obj_normal);
	free(obj_normal);
	transpose(&obj->inv_transform);
	normalize(&world_normal);
	return (world_normal);
}

/* returns the normal vector at a point on the surface of the object*/
double	*get_normal_at(t_object *obj, double *w_point)
{
	double	*normal_vector;

	if (!strncmp(obj->id, "pl\0", 3))
		normal_vector = tupledup(obj->orientation_vector, 4);
	else if (!strncmp(obj->id, "sp\0", 3))
		normal_vector = get_sphere_normal_at(obj, w_point);
	else if (!strncmp(obj->id, "cy\0", 3))
		normal_vector = get_cylinder_normal_at(obj, w_point);
	else if (!strncmp(obj->id, "co\0", 3))
		normal_vector = get_cone_normal_at(obj, w_point);
	else
		normal_vector = NULL;
	return (normal_vector);
}
