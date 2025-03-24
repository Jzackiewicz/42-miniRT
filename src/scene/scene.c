/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:42:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/24 18:48:09 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/* default world initializer
	takes an array of objects and the light + ambient data */
t_world	*create_world(t_camera *cam_data, t_light *light, t_ambient *ambient,
		t_object **objs)
{
	t_world	*world;

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

	comps->t = intersection->t;
	comps->obj = intersection->object;
	comps->point = position(ray, comps->t);
	comps->eyev = ray->direction;
	comps->normalv = get_normal_at(intersection->object, comps->point);
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = negate_tuple(comps->normalv);
	}
	else
		comps->inside = false;
	return (comps);
}

t_comps **get_comps_for_all_intersections(t_intersec ***world_intersections)
{
	int i;
	int limit;
	t_comps **intersection_computations;
	
	i = -1;
	limit = count_intersections(*world_intersections);
	while (++i < limit)
	{
		intersection_computations[i] = prepare_computations((*world_intersections)[i], <ray>); // ray placeholder (which ray?)
	}
	return (intersection_computations);
}

/* The function returns the color at the intersection
	encapsulated by comps, in the given world. */
double	shade_hit(t_world *world, t_comps *comps)
{
	return (lighting(world->light, comps->obj, world->camera, comps->normalv,
			comps->eyev));
}