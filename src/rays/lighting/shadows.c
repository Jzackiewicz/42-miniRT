/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:23:41 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/30 12:40:53 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static t_intersec	*precompute_shadows(double *worldp, double *lightv,
		t_object **objs)
{
	t_ray		*ray;
	t_intersec	**i_s;
	t_intersec	*hit;

	ray = create_ray(worldp, lightv);
	i_s = get_sorted_intersections(ray, objs);
	free(ray);
	hit = identify_hit(i_s);
	free_intersections(i_s);
	return (hit);
}

/* func to determine if a point belongs in the shadow or not
   takes a world and a point as parameters.
	objs are passed to match our get_intersections() implemenation

	The algorithm:
	1. 	measure the distance
	2. 	create a ray from point toward the light source by normalizing the
			vector from step 1
	3. 	intersect the world with that ray
	4. 	check if there's a hit
 */
bool	is_shadowed(t_world *w, double *worldp, int light_index)
{
	t_intersec	*hit;
	double		*lightv;
	double		distance;
	bool		state;

	lightv = subtract_tuple(w->lights[light_index]->coords, worldp);
	distance = magnitude(lightv);
	normalize(&lightv);
	hit = precompute_shadows(worldp, lightv, w->objs);
	free(lightv);
	if (hit && hit->t < distance)
		state = true;
	else
		state = false;
	free(hit);
	return (state);
}
