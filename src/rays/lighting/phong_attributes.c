/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:42:38 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/17 14:03:01 by agarbacz         ###   ########.fr       */
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

/**
 * A utility func for apply_phong_attributes() func
 *  to calculate the light contribution for all light sources
 *
 * @param: phong_lighting: the final colors of the pixel
 *
 * @var l_id: the current's light source index in the lights array
 * @var diff: the diffuse contribution
 * @var spec: the specular contribution
 * @var shadow: a boolean indicating if the current pixel should be shadowed
 *
 * @return None, the function modifies the phong lighting parameter in-place
 */
static void	add_light_contribution(t_world *w, t_comps *c, double *new_color,
		double *phong_lighting)
{
	int		l_id;
	int		i;
	double	diff;
	double	spec;
	bool	shadow;

	l_id = -1;
	while (w->lights[++l_id])
	{
		shadow = is_shadowed(w, c->over_point, l_id);
		if (!shadow)
		{
			diff = get_diffuse(w->lights[l_id]->coords, c->normalv, c->point);
			spec = get_specular(w->lights[l_id]->coords,
					w->camera->orientation_vector, c->normalv, c->point);
			i = -1;
			while (++i < 3)
			{
				phong_lighting[i] += diff * w->lights[l_id]->color[i]
					* w->lights[l_id]->brightness / 255.0 * new_color[i];
				phong_lighting[i] += spec * w->lights[l_id]->color[i]
					* w->lights[l_id]->brightness;
			}
		}
	}
}

/**
 * this func applies the Phong reflection model to calculate the
 * final color of a point in a scene- meaning the color of a pixel.
 *
 * @param world: the world struct containing all the scene's arrays
 * 					with objects, lights, and camera.
 * @param comps: the computations struct containing the object, the point,
 *               the eye vector, and the normal vector.
 * @param new_color: the final color of the point.
 *
 * @return the final color of the point, after applying the Phong reflection
 *         model.
 *
 * The algorithm:
 * 		1. init the color channels with the ambient color channels.
 * 		2. loop through all the lights in the scene.
 * 			2a. check if the light is shadowed.
 * 			2b. if not shadowed, calculate the diffuse and specular
 * 				components of the light.
 *			2c. Add the diffuse and specular components to the color channels.
 */
double	*apply_phong_attributes(t_world *world, t_comps *comps,
		double *new_color)
{
	double	*phong_lighting;
	int		i;

	phong_lighting = (double *)malloc(sizeof(double) * 3);
	i = -1;
	while (++i < 3)
	{
		phong_lighting[i] = world->ambient->brightness
			* world->ambient->color[i] / 255.0 * new_color[i];
	}
	add_light_contribution(world, comps, new_color, phong_lighting);
	return (phong_lighting);
}
