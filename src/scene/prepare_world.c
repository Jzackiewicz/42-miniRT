/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:42:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 11:05:18 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/* returns the normal vector at a point on the surface of the sphere*/
static double	*get_normal_at(t_object *obj, double *w_point)
{
	double	*object_center;
	double	*obj_normal;
	double	*obj_point;
	double	*world_normal;

	object_center = init_tuple(1);
	obj_point = multiply_tuple_and_matrix(obj->inv_transform, w_point);
	if (!strncmp(obj->id, "pl\0", 3))
		return(tupledup(obj->orientation_vector));
	else if (!strncmp(obj->id, "sp\0", 3))
		obj_normal = subtract_tuple(obj_point, object_center);
	else
		obj_normal = init_tuple(0);
	free(obj_point);
	normalize(&obj_normal);
	transpose(&obj->inv_transform);
	world_normal = multiply_tuple_and_matrix(obj->inv_transform, obj_normal);
	transpose(&obj->inv_transform);
	normalize(&world_normal);
	free(object_center);
	free(obj_normal);
	return (world_normal);
}

/* static double	*get_normal_at(t_object *obj, double *w_point)
{
	double	*normal;
	
	if (!strncmp(obj->id, "pl\0", 3))
		normal = tupledup(obj->orientation_vector);
	else if (!strncmp(obj->id, "sp\0", 3))
		normal = get_sphere_normal_at(obj, w_point);
	else
		normal = init_tuple(0);
	return (normal);
} */

/* default world initializer
	takes an array of objects and the light + ambient data */
t_world	*create_world(t_input_data **input_data, int no_lines)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->objs = get_objects(input_data, no_lines);
	world->camera = get_cam_data(input_data);
	world->light = get_light_data(input_data);
	world->ambient = get_ambient_data(input_data);
	free_input_ids(input_data);
	return (world);
}

t_comps	*prepare_computations(t_intersec *intersection, t_ray *ray)
{
	t_comps	*comps;
	double	*tmp;
	double	*normal_epsilon_product;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = intersection->t;
	comps->obj = intersection->object;
	comps->point = position(ray, comps->t);
	comps->eyev = negate_tuple(ray->direction);
	comps->normalv = get_normal_at(comps->obj, comps->point);
	normal_epsilon_product = multiply_tuple(comps->normalv, EPSILON);
	comps->over_point = add_tuple(comps->point, normal_epsilon_product);
	free(normal_epsilon_product);
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		tmp = comps->normalv;
		comps->normalv = negate_tuple(tmp);
		free(tmp);
	}
	else
		comps->inside = false;
	return (comps);
}
