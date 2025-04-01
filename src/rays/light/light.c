/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/01 18:07:32 by jzackiew         ###   ########.fr       */
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

double	*find_reflection(double *origin, double *normal, double *target)
{
	double	*incidence;
	double	*rev_incidence;
	double	*reflection;
	double	*tmp;
	
	incidence = subtract_tuple(origin, target);
	normalize(&incidence);
	if (dot(incidence, normal) < 0)
		return (free(incidence), NULL);
	rev_incidence = negate_tuple(incidence);
	free(incidence);
	tmp = multiply_tuple(normal, 2 * dot(rev_incidence, normal));
	reflection = subtract_tuple(rev_incidence, tmp);
	free(tmp);
	free(rev_incidence);
	return (reflection);
}

double	get_diffuse(double *light_point, double *object_point, double *normal)
{
	double	*incidence;
	double	angle_of_incidence;
	double	diffuse;
	double	diffuse_factor;
	
	diffuse_factor = 1;
	incidence = subtract_tuple(light_point, object_point);
    normalize(&incidence);
    angle_of_incidence = dot(incidence, normal);
	free(incidence);
	if (angle_of_incidence < 0)
		return (0);
	diffuse = diffuse_factor * angle_of_incidence;
	return (diffuse);
}

double	get_specular(double *light_origin, double *cam_v, double *normal, double *target)
{
	double	*reflection;
	double	*camera_vector;
	double	angle_of_reflection;
	double	specular;
	double	specular_factor = 1;
	double	shininess = 400;
	
	reflection = find_reflection(light_origin, target, normal);
	if (!reflection)
		return (0);
	camera_vector = subtract_tuple(cam_v, target);
	normalize(&camera_vector);
	normalize(&reflection);
	angle_of_reflection = dot(reflection, camera_vector);
	if (angle_of_reflection <= 0)
		return (0);
	else
		specular = specular_factor * pow(angle_of_reflection, shininess);
	return (specular);
}

double lighting(t_light *light, t_object *obj, t_camera *cam_data, t_ambient *ambient_data,
        double *normal, double *target)
{
    double ambient;
	double	diffuse;
	double	specular;
    double r = obj->color[0];
    double g = obj->color[1];
    double b = obj->color[2];
    double light_r = light->color[0] / 255.0;
    double light_g = light->color[1] / 255.0;
    double light_b = light->color[2] / 255.0;

	diffuse = get_diffuse(light->coords, normal, target);
	specular = get_specular(light->coords, cam_data->orientation_vector, normal, target);
	ambient = ambient_data->brightness;
	
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

    return rgb_to_int(result_r, result_g, result_b);
}
