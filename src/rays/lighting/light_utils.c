/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:35:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/04 20:14:05 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

int	rgb_to_int(double r, double g, double b)
{
	r = fmin(255, fmax(0, r));
	g = fmin(255, fmax(0, g));
	b = fmin(255, fmax(0, b));
	return (((int)r << 16) | ((int)g << 8) | (int)b);
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
