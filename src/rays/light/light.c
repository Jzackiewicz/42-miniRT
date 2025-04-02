/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/02 18:34:32 by jzackiew         ###   ########.fr       */
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

double	*find_reflection(double *lightp, double *normal, double *objectp)
{
	double	*lightv;
	double	*rev_lightv;
	double	*reflection;
	double	*tmp;
	
	lightv = subtract_tuple(lightp, objectp);
	normalize(&lightv);
	if (dot(lightv, normal) < 0)
		return (free(lightv), NULL);
	rev_lightv = negate_tuple(lightv);
	free(lightv);
	tmp = multiply_tuple(normal, 2 * dot(lightv, normal));
	reflection = subtract_tuple(lightv, tmp);
	free(tmp);
	free(rev_lightv);
	return (reflection);
}

double	get_diffuse(double *lightp, double *normal, double *objectp)
{
	double	*lightv;
	double	angle_of_incidence;
	double	diffuse;
	double	diffuse_factor;
	
	diffuse_factor = 1;
	lightv = subtract_tuple(lightp, objectp);
    normalize(&lightv);
    angle_of_incidence = dot(lightv, normal);
	free(lightv);
	if (angle_of_incidence < 0)
		return (0);
	diffuse = diffuse_factor * angle_of_incidence;
	return (diffuse);
}

double	get_specular(double *light_origin, double *cam_v, double *normal, double *target)
{
	double	*reflection;
	double	angle_of_reflection;
	double	specular;
	double	specular_factor = 1;
	double	shininess = 20;
	
	reflection = find_reflection(light_origin, target, normal);
	if (!reflection)
		return (0);
	normalize(&reflection);
	angle_of_reflection = dot(reflection, cam_v);
	if (angle_of_reflection <= 0)
		return (0);
	else
		specular = specular_factor * pow(angle_of_reflection, shininess);
	return (specular);
}

double lighting(t_world *world, t_comps *comps)
{
    double ambient;
	double	diffuse;
	double	specular;
    double r = comps->obj->color[0];
    double g = comps->obj->color[1];
    double b = comps->obj->color[2];
    double light_r = world->light->color[0] / 255.0;
    double light_g = world->light->color[1] / 255.0;
    double light_b = world->light->color[2] / 255.0;

	diffuse = get_diffuse(world->light->coords, comps->normalv, comps->point);
	specular = get_specular(world->light->coords, world->camera->orientation_vector, comps->normalv, comps->point);
	ambient = world->ambient->brightness;
	
    double effective_ambient_r = ambient * light_r * world->light->brightness;
    double effective_ambient_g = ambient * light_g * world->light->brightness;
    double effective_ambient_b = ambient * light_b * world->light->brightness;

    double effective_diffuse_r = diffuse * light_r * world->light->brightness;
    double effective_diffuse_g = diffuse * light_g * world->light->brightness;
    double effective_diffuse_b = diffuse * light_b * world->light->brightness;

    double effective_specular_r = specular * light_r * world->light->brightness;
    double effective_specular_g = specular * light_g * world->light->brightness;
    double effective_specular_b = specular * light_b * world->light->brightness;

    // color by color for precisio
    int result_r = fmin(255, r * effective_ambient_r + r * effective_diffuse_r + 255 * effective_specular_r);
    int result_g = fmin(255, g * effective_ambient_g + g * effective_diffuse_g + 255 * effective_specular_g);
    int result_b = fmin(255, b * effective_ambient_b + b * effective_diffuse_b + 255 * effective_specular_b);
    return rgb_to_int(result_r, result_g, result_b);
}
