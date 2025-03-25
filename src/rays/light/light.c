/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 11:51:04 by jzackiew         ###   ########.fr       */
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
	res = subtract_tuple(in, res);
	return (res);
}

// p. 88 book
// TODO: refactor lol
double lighting(t_light *light, t_object *obj, t_camera *cam_data,
        double *normal, double *point)
{
    double *light_p;
    double *light_v;
    double *reflect_v;
    double *view_v;
    double reflect_dot_eye;
    double ambient, light_dot_normal, diffuse, specular;
    double r = obj->color[0];
    double g = obj->color[1];
    double b = obj->color[2];
    double light_r = light->color[0] / 255.0;
    double light_g = light->color[1] / 255.0;
    double light_b = light->color[2] / 255.0;

    light_p = init_tuple(1);
    ft_memcpy(light_p, light->coords, sizeof(double) * 4);
    light_v = subtract_tuple(light_p, point);
    normalize(&light_v);

	// view vector (tried to fix the specular :(( )
    view_v = subtract_tuple(cam_data->origin, point);
    normalize(&view_v);

    ambient = obj->material->ambient;
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
        reflect_dot_eye = dot(reflect_v, view_v);
        if (reflect_dot_eye <= 0)
            specular = 0;
        else
            specular = obj->material->specular * pow(reflect_dot_eye, obj->material->shininess);
        free(reflect_v);
    }
    double effective_ambient_r = ambient * light_r * light->brightness;
    double effective_ambient_g = ambient * light_g * light->brightness;
    double effective_ambient_b = ambient * light_b * light->brightness;

    double effective_diffuse_r = diffuse * light_r * light->brightness;
    double effective_diffuse_g = diffuse * light_g * light->brightness;
    double effective_diffuse_b = diffuse * light_b * light->brightness;

    double effective_specular_r = specular * light_r * light->brightness;
    double effective_specular_g = specular * light_g * light->brightness;
    double effective_specular_b = specular * light_b * light->brightness;

    // color by color for precision
    int result_r = fmin(255, r * effective_ambient_r + r * effective_diffuse_r + 255 * effective_specular_r);
    int result_g = fmin(255, g * effective_ambient_g + g * effective_diffuse_g + 255 * effective_specular_g);
    int result_b = fmin(255, b * effective_ambient_b + b * effective_diffuse_b + 255 * effective_specular_b);

    free(light_p);
    free(light_v);
    free(view_v);
    return rgb_to_int(result_r, result_g, result_b);
}
