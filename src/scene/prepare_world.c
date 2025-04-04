/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:42:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/04 12:20:54 by agarbacz         ###   ########.fr       */
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
	world->objs = get_objects(input_data, no_lines);
	world->camera = get_cam_data(input_data);
	world->light = get_light_data(input_data);
	world->ambient = get_ambient_data(input_data);
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

void	free_comps(t_comps *comps)
{
	free(comps->point);
	free(comps->eyev);
	free(comps->normalv);
	free(comps);
}
