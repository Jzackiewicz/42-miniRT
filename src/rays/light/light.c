/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/03 14:21:17 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static int	rgb_to_int(double r, double g, double b)
{
	r = fmin(255, fmax(0, r));
	g = fmin(255, fmax(0, g));
	b = fmin(255, fmax(0, b));
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

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
	free(obj_point);
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
	double	*reflection;
	double	*tmp;

	lightv = subtract_tuple(lightp, objectp);
	normalize(&lightv);
	if (dot(lightv, normal) < 0)
		return (free(lightv), NULL);
	tmp = multiply_tuple(normal, 2 * dot(lightv, normal));
	reflection = subtract_tuple(lightv, tmp);
	free(tmp);
	free(lightv);
	return (reflection);
}

double	get_diffuse(double *lightp, double *normal, double *objectp)
{
	double	*lightv;
	double	angle_of_incidence;
	double	diffuse;
	double	diffuse_factor;

	diffuse_factor = 0.7;
	lightv = subtract_tuple(lightp, objectp);
	normalize(&lightv);
	angle_of_incidence = dot(lightv, normal);
	free(lightv);
	if (angle_of_incidence < 0)
		return (0);
	diffuse = diffuse_factor * angle_of_incidence;
	return (diffuse);
}

double	get_specular(double *light_origin, double *cam_v, double *normal,
		double *target)
{
	double	*reflection;
	double	angle_of_reflection;
	double	specular;
	double	specular_factor;
	double	shininess;

	specular_factor = 0.6;
	shininess = 50;
	reflection = find_reflection(light_origin, normal, target);
	if (!reflection)
		return (0);
	normalize(&reflection);
	angle_of_reflection = dot(reflection, cam_v);
	free(reflection);
	if (angle_of_reflection <= 0)
		return (0);
	else
		specular = specular_factor * pow(angle_of_reflection, shininess);
	return (specular);
}

static int	calc_shadow(t_comps *comps, t_world *world)
{
	double	s_r;
	double	s_g;
	double	s_b;

	s_r = comps->obj->color[0] * world->ambient->color[0] / 255.0
		* world->ambient->brightness;
	s_g = comps->obj->color[1] * world->ambient->color[1] / 255.0
		* world->ambient->brightness;
	s_b = comps->obj->color[2] * world->ambient->color[2] / 255.0
		* world->ambient->brightness;
	return (rgb_to_int(s_r, s_g, s_b));
}

double	*assign_rgb(t_comps *comps)
{
	double	*rgb;

	rgb = malloc((3) * sizeof(double));
	if (!rgb)
		return (NULL);
	rgb[0] = comps->obj->color[0];
	rgb[1] = comps->obj->color[1];
	rgb[2] = comps->obj->color[2];
	return (rgb);
}

double	*assign_light_colors(t_world *world)
{
	double	*light_rgb;

	light_rgb = malloc(3 * sizeof(double));
	if (!light_rgb)
		return (NULL);
	light_rgb[0] = world->light->color[0] / 255.0;
	light_rgb[1] = world->light->color[1] / 255.0;
	light_rgb[2] = world->light->color[2] / 255.0;
	return (light_rgb);
}

double	*assign_effective_ambient(t_world *world, double *light_rgb)
{
	double	*effective_ambient;

	effective_ambient = malloc(3 * sizeof(double));
	if (!effective_ambient)
		return (NULL);
	effective_ambient[0] = world->ambient->brightness * light_rgb[0]
		* world->light->brightness;
	effective_ambient[1] = world->ambient->brightness * light_rgb[1]
		* world->light->brightness;
	effective_ambient[2] = world->ambient->brightness * light_rgb[2]
		* world->light->brightness;
	return (effective_ambient);
}

double	*assign_effective_diffuse(double diffuse, double *light_rgb,
		t_world *world)
{
	double	*effective_diffuse_rgb;

	effective_diffuse_rgb = malloc(3 * sizeof(double));
	if (!effective_diffuse_rgb)
		return (NULL);
	effective_diffuse_rgb[0] = diffuse * light_rgb[0]
		* world->light->brightness;
	effective_diffuse_rgb[1] = diffuse * light_rgb[1]
		* world->light->brightness;
	effective_diffuse_rgb[2] = diffuse * light_rgb[2]
		* world->light->brightness;
	return (effective_diffuse_rgb);
}

double	*assign_effective_specular(double specular, double *light_rgb,
		t_world *world)
{
	double	*effective_specular_rgb;

	effective_specular_rgb = malloc(3 * sizeof(double));
	if (!effective_specular_rgb)
		return (NULL);
	effective_specular_rgb[0] = specular * light_rgb[0]
		* world->light->brightness;
	effective_specular_rgb[1] = specular * light_rgb[1]
		* world->light->brightness;
	effective_specular_rgb[2] = specular * light_rgb[2]
		* world->light->brightness;
	return (effective_specular_rgb);
}
void free_phong_utils()
{
	
}


double	calc_res_color(double *rgb, double *effective_ambient,
		double *effective_diffuse, double *effective_specular)
{
	double	res[3];
	
	res[0] = fmin(255, rgb[0] * effective_ambient[0] + rgb[0]
			* effective_diffuse[0] + 255 * effective_specular[0]);
	res[1] = fmin(255, rgb[1] * effective_ambient[1] + rgb[1]
			* effective_diffuse[1] + 255 * effective_specular[1]);
	res[2] = fmin(255, rgb[2] * effective_ambient[2] + rgb[2]
			* effective_diffuse[2] + 255 * effective_specular[2]);
	return (rgb_to_int(res[0], res[1], res[2]));
}

double	lighting(t_world *world, t_comps *comps)
{
	double	diffuse;
	double	specular;
	double	*rgb;
	double	*light_rgb;
	double	*effective_ambient_rgb;
	double	*effective_diffuse_rgb;
	double	*effective_specular_rgb;

	if (is_shadowed(world, comps->over_point))
		return (calc_shadow(comps, world));
	rgb = assign_rgb(comps);
	light_rgb = assign_light_colors(world);
	diffuse = get_diffuse(world->light->coords, comps->normalv, comps->point);
	specular = get_specular(world->light->coords,
			world->camera->orientation_vector, comps->normalv, comps->point);
	effective_ambient_rgb = assign_effective_ambient(world, light_rgb);
	effective_diffuse_rgb = assign_effective_diffuse(diffuse, light_rgb, world);
	effective_specular_rgb = assign_effective_specular(specular, light_rgb,
			world);
	free(light_rgb);
	return (calc_res_color(rgb, effective_ambient_rgb, effective_diffuse_rgb,
			effective_specular_rgb));
}
