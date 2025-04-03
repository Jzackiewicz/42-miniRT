/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/03 16:42:58 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

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

static void	free_phong_colors(double *rgb, double *effective_ambient,
		double *effective_diffuse, double *effective_specular)
{
	free(rgb);
	free(effective_ambient);
	free(effective_diffuse);
	free(effective_specular);
}

static double	calc_res_color(double *rgb, double *effective_ambient,
		double *effective_diffuse, double *effective_specular)
{
	double	res[3];

	res[0] = fmin(255, rgb[0] * effective_ambient[0] + rgb[0]
			* effective_diffuse[0] + 255 * effective_specular[0]);
	res[1] = fmin(255, rgb[1] * effective_ambient[1] + rgb[1]
			* effective_diffuse[1] + 255 * effective_specular[1]);
	res[2] = fmin(255, rgb[2] * effective_ambient[2] + rgb[2]
			* effective_diffuse[2] + 255 * effective_specular[2]);
	free_phong_colors(rgb, effective_ambient, effective_diffuse,
		effective_specular);
	return (rgb_to_int(res[0], res[1], res[2]));
}

double	lighting(t_world *world, t_comps *comps)
{
	double	*rgb;
	double	*light_rgb;
	double	*effective_ambient_rgb;
	double	*effective_diffuse_rgb;
	double	*effective_specular_rgb;

	if (is_shadowed(world, comps->over_point))
		return (calc_shadow(comps, world));
	rgb = assign_rgb(comps);
	light_rgb = assign_light_colors(world);
	effective_ambient_rgb = assign_effective_ambient(world, light_rgb);
	effective_diffuse_rgb = assign_effective_diffuse(light_rgb, world, comps);
	effective_specular_rgb = assign_effective_specular(light_rgb, world, comps);
	free(light_rgb);
	return (calc_res_color(rgb, effective_ambient_rgb, effective_diffuse_rgb,
			effective_specular_rgb));
}
