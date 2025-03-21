/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/21 14:56:21 by agarbacz         ###   ########.fr       */
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

	sphere_center = init_tuple(1);
	obj_point = multiply_tuple_and_matrix(obj->inv_transform, w_point);
	obj_normal = subtract_tuple(obj_point, sphere_center);
	normalize(&obj_normal);
	world_normal = multiply_tuple_and_matrix(obj->inv_transform, obj_normal);
	normalize(&world_normal);
	free(sphere_center);
	free(obj_normal);
	// print_tuple(world_normal);
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
double	lighting(t_light *light, t_object *obj, t_camera *cam_data,
		double *normal, double *point)
{
	int		effective_color;
	double *light_p;
	double *light_v;
	double *reflect_v;
	double reflect_dot_eye;
	double ambient;
    double light_dot_normal;
    double diffuse;
	double specular;

	effective_color = rgb_to_int(obj->color[0], obj->color[1], obj->color[2]) * light->brightness;

	light_p = init_tuple(1);	
	ft_memcpy(light_p, light->coords, sizeof(double) * 4);
	light_v = subtract_tuple(light_p, point);
	normalize(&light_v);

	ambient = (double) effective_color * obj->material->ambient;

	light_dot_normal = dot(light_v, normal);
	if (light_dot_normal < 0)
    {
		diffuse = 0;
		specular = 0;
	}
	else
	{
		diffuse = (double) effective_color * obj->material->diffuse * light_dot_normal;
		reflect_v = reflect(negate_tuple(light_v), normal);
		reflect_dot_eye = dot(reflect_v, cam_data->orientation_vector);
		if (reflect_dot_eye <= 0)
			specular = 0;
		else
			specular = light->brightness * obj->material->specular * pow(reflect_dot_eye, obj->material->shininess);
	}
	return (ambient + diffuse + specular);
}
