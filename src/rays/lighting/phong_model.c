/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/04 20:13:15 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static double	*assign_effective_ambient(t_world *world, double *light_rgb)
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

static double	*assign_effective_diffuse(double *light_rgb, t_world *world,
		t_comps *comps)
{
	double	diffuse;
	double	*effective_diffuse_rgb;

	effective_diffuse_rgb = malloc(3 * sizeof(double));
	if (!effective_diffuse_rgb)
		return (NULL);
	diffuse = get_diffuse(world->light->coords, comps->normalv, comps->point);
	effective_diffuse_rgb[0] = diffuse * light_rgb[0]
		* world->light->brightness;
	effective_diffuse_rgb[1] = diffuse * light_rgb[1]
		* world->light->brightness;
	effective_diffuse_rgb[2] = diffuse * light_rgb[2]
		* world->light->brightness;
	return (effective_diffuse_rgb);
}

static double	*assign_effective_specular(double *light_rgb, t_world *world,
		t_comps *comps)
{
	double	*effective_specular_rgb;
	double	specular;

	effective_specular_rgb = malloc(3 * sizeof(double));
	if (!effective_specular_rgb)
		return (NULL);
	specular = get_specular(world->light->coords,
			world->camera->orientation_vector, comps->normalv, comps->point);
	effective_specular_rgb[0] = specular * light_rgb[0]
		* world->light->brightness;
	effective_specular_rgb[1] = specular * light_rgb[1]
		* world->light->brightness;
	effective_specular_rgb[2] = specular * light_rgb[2]
		* world->light->brightness;
	return (effective_specular_rgb);
}

double	apply_phong_model(t_world *world, t_comps *comps)
{
	double	res[3];
	double	*light_rgb;
	double	*effective_ambient;
	double	*effective_diffuse;
	double	*effective_specular;

	light_rgb = assign_light_colors(world);
	effective_ambient = assign_effective_ambient(world, light_rgb);
	effective_diffuse = assign_effective_diffuse(light_rgb, world, comps);
	effective_specular = assign_effective_specular(light_rgb, world, comps);
	free(light_rgb);
	res[0] = fmin(255, comps->obj->color[0] * effective_ambient[0]
			+ comps->obj->color[0] * effective_diffuse[0] + 255
			* effective_specular[0]);
	res[1] = fmin(255, comps->obj->color[1] * effective_ambient[1]
			+ comps->obj->color[1] * effective_diffuse[1] + 255
			* effective_specular[1]);
	res[2] = fmin(255, comps->obj->color[2] * effective_ambient[2]
			+ comps->obj->color[2] * effective_diffuse[2] + 255
			* effective_specular[2]);
	free(effective_ambient);
	free(effective_diffuse);
	free(effective_specular);
	return (rgb_to_int(res[0], res[1], res[2]));
}
