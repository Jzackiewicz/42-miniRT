/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:42:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/01 16:16:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/* default world initializer
	takes an array of objects and the light + ambient data */
t_world	*create_world(t_input_data **input_data, int no_lines)
{
	t_world	*world;

	world = (t_world *)malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->light = get_light_data(input_data);
	world->objs = get_objects(input_data, no_lines);
	world->ambient = get_ambient_data(input_data);
	world->camera = get_cam_data(input_data);
	return (world);
}

t_comps	*prepare_computations(t_intersec *intersection, t_ray *ray)
{
	t_comps	*comps;

	comps = malloc(sizeof(t_comps));
	if (!comps)
		return (NULL);
	comps->t = intersection->t;
	comps->obj = intersection->object;
	comps->point = position(ray, comps->t);
	comps->eyev = negate_tuple(ray->direction);
	comps->normalv = get_normal_at(comps->obj, comps->point);
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = negate_tuple(comps->normalv);
	}
	else
		comps->inside = false;
	return (comps);
}

/* The function returns the color at the intersection
encapsulated by comps, in the given world. */
double	shade_hit(t_world *world, t_comps *comps)
{
	return (lighting(world->light, comps->obj, world->camera, world->ambient,
			comps->normalv, comps->point));
}

double	color_at(t_world *world, t_ray *ray)
{
	t_intersec	**intersections;
	t_intersec	*hit;
	t_comps		*comps;
	double		result;

	result = 0;
	intersections = get_sorted_intersections(ray, world->objs);
	hit = identify_hit(intersections);
	if (hit)
	{
		comps = prepare_computations(hit, ray);
		result = shade_hit(world, comps);
		free(comps);
	}
	else
		result = 0;
	free_intersections(intersections);
	return (result);
}
