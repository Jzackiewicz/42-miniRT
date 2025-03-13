/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_inits.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:48:44 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/13 12:49:30 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

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

double	*init_result_t(void)
{
	double	*result_t;

	result_t = (double *)malloc(sizeof(double) * 2);
	if (!result_t)
		return (NULL);
	return (result_t);
}
