/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:42:38 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/15 11:52:24 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static double	get_diffuse(double *lightp, double *normal, double *objectp)
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

static double	*find_reflection(double *lightp, double *normal,
		double *objectp)
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

static double	get_specular(double *light_origin, double *cam_v,
		double *normal, double *target)
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

double	*apply_phong_attributes(t_world *world, t_comps *comps,
		double *new_color)
{
	double	*phong_lighting;
	double	diffuse;
	double	specular;
	bool	shadow_flag;
	int		i;

	phong_lighting = (double *)malloc(sizeof(double) * 3);
	diffuse = get_diffuse(world->light->coords, comps->normalv, comps->point);
	specular = get_specular(world->light->coords,
			world->camera->orientation_vector, comps->normalv, comps->point);
	shadow_flag = is_shadowed(world, comps->over_point);
	i = -1;
	while (++i < 3)
	{
		phong_lighting[i] = world->ambient->brightness
			* world->ambient->color[i] / 255.0 * new_color[i];
		if (shadow_flag)
			continue ;
		phong_lighting[i] += diffuse * world->light->color[i]
			* world->light->brightness / 255.0 * new_color[i];
		phong_lighting[i] += specular * world->light->color[i]
			* world->light->brightness / 255.0 * new_color[i];
	}
	return (phong_lighting);
}
