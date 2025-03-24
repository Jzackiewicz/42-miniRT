/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/21 18:55:15 by agarbacz         ###   ########.fr       */
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
	transpose(&obj->inv_transform);
	world_normal = multiply_tuple_and_matrix(obj->inv_transform, obj_normal);
	transpose(&obj->inv_transform);
	normalize(&world_normal);
	free(sphere_center);
	free(obj_normal);
	return (world_normal);
}

double	*reflect(double *in, double *normal)
{
	double	*res;

	res = multiply_tuple(normal, 2 * dot(in, normal));
	res = subtract_tuple(res, in);
	return (res);
}

// p. 88 book
// TODO: refactor lol
// specular is not visible for some reason
double lighting(t_light *light, t_object *obj, t_camera *cam_data,
        double *normal, double *point)
{
    double *light_p;
    double *light_v;
    double *reflect_v;
    double reflect_dot_eye;
    double ambient, light_dot_normal, diffuse, specular;
    double r = obj->color[0];
    double g = obj->color[1];
    double b = obj->color[2];
    double total_light;
    double light_r = light->color[0] / 255.0;
    double light_g = light->color[1] / 255.0;
    double light_b = light->color[2] / 255.0;

    light_p = init_tuple(1);
    ft_memcpy(light_p, light->coords, sizeof(double) * 4);
    light_v = subtract_tuple(light_p, point);
    normalize(&light_v);

    light_dot_normal = dot(light_v, normal);
    if (light_dot_normal < 0)
    {
        diffuse = 0;
        specular = 0;
    }
    else
    {
        diffuse = obj->material->diffuse * light_dot_normal;
        reflect_v = reflect(negate_tuple(light_v), normal);
        reflect_dot_eye = dot(reflect_v, cam_data->orientation_vector);
        if (reflect_dot_eye <= 0)
            specular = 0;
        else
            specular = obj->material->specular * pow(reflect_dot_eye, obj->material->shininess);
        free(reflect_v);
    }
    ambient = obj->material->ambient * light->brightness;

    // split colors for each channel for more color precision :))
    int result_r = fmin(255, r * (ambient * light_r + light->brightness * diffuse * light_r + light->brightness * specular));
    int result_g = fmin(255, g * (ambient * light_g + light->brightness * diffuse * light_g + light->brightness * specular));
    int result_b = fmin(255, b * (ambient * light_b + light->brightness * diffuse * light_b + light->brightness * specular));

    free(light_p);
    free(light_v);
    return rgb_to_int(result_r, result_g, result_b);
}

