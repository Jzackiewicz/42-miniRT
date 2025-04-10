/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/10 12:31:10 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static double	*assign_effective_ambient(t_world *world, t_comps *comps)
{
	double	*effective_ambient;

	effective_ambient = malloc(3 * sizeof(double));
	if (!effective_ambient)
		return (NULL);
	effective_ambient[0] = world->ambient->brightness * world->ambient->color[0]
		/ 255.0 * comps->obj->color[0];
	effective_ambient[1] = world->ambient->brightness * world->ambient->color[1]
		/ 255.0 * comps->obj->color[1];
	effective_ambient[2] = world->ambient->brightness * world->ambient->color[2]
		/ 255.0 * comps->obj->color[2];
	return (effective_ambient);
}

static double	*assign_effective_diffuse(t_world *world, t_comps *comps)
{
	double	diffuse;
	double	*effective_diffuse_rgb;

	effective_diffuse_rgb = malloc(3 * sizeof(double));
	if (!effective_diffuse_rgb)
		return (NULL);
	diffuse = get_diffuse(world->light->coords, comps->normalv, comps->point);
	effective_diffuse_rgb[0] = diffuse * world->light->color[0]
		* world->light->brightness;
	effective_diffuse_rgb[1] = diffuse * world->light->color[1]
		* world->light->brightness;
	effective_diffuse_rgb[2] = diffuse * world->light->color[2]
		* world->light->brightness;
	return (effective_diffuse_rgb);
}

static double	*assign_effective_specular(t_world *world, t_comps *comps)
{
	double	*effective_specular_rgb;
	double	specular;

	effective_specular_rgb = malloc(3 * sizeof(double));
	if (!effective_specular_rgb)
		return (NULL);
	specular = get_specular(world->light->coords,
			world->camera->orientation_vector, comps->normalv, comps->point);
	effective_specular_rgb[0] = specular * world->light->color[0]
		* world->light->brightness;
	effective_specular_rgb[1] = specular * world->light->color[1]
		* world->light->brightness;
	effective_specular_rgb[2] = specular * world->light->color[2]
		* world->light->brightness;
	return (effective_specular_rgb);
}

int	apply_phong_model(t_world *world, t_comps *comps)
{
	double	res[3];
	double	*effective_ambient;
	double	*effective_diffuse;
	double	*effective_specular;

	effective_ambient = assign_effective_ambient(world, comps);
	if (is_shadowed(world, comps->over_point))
		return (rgb_to_int(effective_ambient));
	effective_diffuse = assign_effective_diffuse(world, comps);
	effective_specular = assign_effective_specular(world, comps);
	res[0] = fmin(255, effective_ambient[0] + effective_diffuse[0]
			+ effective_specular[0]);
	res[1] = fmin(255, effective_ambient[1] + effective_diffuse[1]
			+ effective_specular[1]);
	res[2] = fmin(255, effective_ambient[2] + effective_diffuse[2]
			+ effective_specular[2]);
	free(effective_ambient);
	free(effective_diffuse);
	free(effective_specular);
	return (rgb_to_int(res));
}
