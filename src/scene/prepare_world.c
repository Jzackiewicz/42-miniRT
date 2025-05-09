/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:14:54 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/29 17:07:35 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/* default world initializer
	takes an array of objects and the light + ambient data */
t_world	*create_world(t_input_data **input_data)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->objs = get_objects(input_data);
	world->camera = get_cam_data(input_data);
	world->lights = get_light_data(input_data);
	world->ambient = get_ambient_data(input_data);
	free_input_ids(input_data);
	return (world);
}

t_comps	*prepare_computations(t_intersec *intersection, t_ray *ray)
{
	t_comps	*comps;
	double	*tmp;
	double	*normal_epsilon_product;

	comps = (t_comps *)malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = intersection->t;
	comps->obj = intersection->object;
	comps->point = position(ray, comps->t);
	comps->eyev = negate_tuple(ray->direction);
	comps->normalv = get_normal_at(comps->obj, comps->point);
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		tmp = comps->normalv;
		comps->normalv = negate_tuple(tmp);
		free(tmp);
	}
	normal_epsilon_product = multiply_tuple(comps->normalv, EPSILON);
	comps->over_point = add_tuple(comps->point, normal_epsilon_product);
	free(normal_epsilon_product);
	return (comps);
}
