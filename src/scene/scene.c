/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:42:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 11:32:28 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/* default world initializer
	takes an array of objects and the light + ambient data */
t_world	*create_world(t_camera *cam_data, t_light *light, t_ambient *ambient,
		t_object **objs)
{
	t_world	*world;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->light = light;
	world->objs = objs;
	world->ambient = ambient;
	world->camera = cam_data;
	return (world);
}

/* creates an array of all ray-object intersections sorted ascendingly */
t_intersec	***intersect_world(t_ray **rays, t_object **objs)
{
	int			i;
	int			ray_count;
	t_intersec	***res;

	i = 0;
	ray_count = 0;
	while (rays[ray_count])
		ray_count++;
	res = (t_intersec ***)malloc(sizeof(t_intersec **) * (ray_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (rays[i])
	{
		res[i] = get_sorted_intersections(rays[i], objs);
		i++;
	}
	res[i] = NULL;
	return (res);
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
	return (lighting(world->light, comps->obj->material, comps->point,
			comps->eyev, comps->normalv));
}

double	color_at(t_world *world, t_ray *ray)
{
	t_intersec **intersections;
	t_intersec *hit;
	t_comps *comps;
	double result;

	intersections = intersect_world(world, ray);
	hit = find_hit(intersections);
	// black if no hit
	if (!hit)
		return (rgb_to_int(0, 0, 0));
	comps = prepare_computations(hit, ray);
	result = shade_hit(world, comps);
	free(comps);
	free_intersections(intersections);
	return (result);
}