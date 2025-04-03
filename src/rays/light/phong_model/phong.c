/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/03 16:45:21 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/miniRT.h"

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

double	*assign_effective_diffuse(double *light_rgb, t_world *world,
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

double	*assign_effective_specular(double *light_rgb, t_world *world,
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
