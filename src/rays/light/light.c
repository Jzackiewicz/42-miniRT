/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/20 13:51:11 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

double	*get_normal_at(t_object *obj, double *w_point)
{
	double *sphere_center;
	double *obj_normal;
	double *obj_point;
	double *world_normal;

	inverse(obj->transform);
	sphere_center = init_tuple(1);
	obj_point = multiply_tuple_and_matrix(obj->transform, w_point);
	obj_normal = subtract_tuple(obj_point, sphere_center);
	normalize(&obj_normal);
	world_normal = multiply_tuple_and_matrix(obj->transform, obj_normal);
	normalize(&world_normal);
	free(sphere_center);
	free(obj_normal);
	return (world_normal);
}


