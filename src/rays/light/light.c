/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/20 15:13:29 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/* returns the normal vector at a point on the surface of the object
	works only for a sphere for now */
double	*get_normal_at(t_object *obj, double *w_point)
{
	double	*sphere_center;
	double	*obj_normal;
	double	*obj_point;
	double	*world_normal;

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

double	*reflect(double *in, double *normal)
{
	double	*res;

	res = multiply_tuple(normal, 2 * dot(in, normal));
	res = subtract_tuple(in, res);
	return (res);
}
// p. 88 book
double	*lighting(t_light *light, t_object *obj, t_camera *cam_data,
		double *normal)
{
	double effective_color;
	double *light_p;
	double *light_v;
	double *ambient;
	
	effective_color = rgb_to_int(obj->color[0], obj->color[1], obj->color[2]) * light->brightness;
	ft_memcpy(light_p, light->coords, sizeof(double) * 4);
	normalize(subtract_tuple(light_p, cam_data->origin));
	
	
	return ;
}