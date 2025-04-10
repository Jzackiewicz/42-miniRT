/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:35:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/09 19:13:28 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

int	rgb_to_int(double *rgb)
{
	rgb[0] = fmin(255, fmax(0, rgb[0]));
	rgb[1] = fmin(255, fmax(0, rgb[1]));
	rgb[2] = fmin(255, fmax(0, rgb[2]));
	return (((int)rgb[0] << 16) | ((int)rgb[1] << 8) | (int)rgb[2]);
}

double	*assign_light_colors(t_world *world)
{
	double	*light_rgb;

	light_rgb = malloc(3 * sizeof(double));
	if (!light_rgb)
		return (NULL);
	light_rgb[0] = world->light->color[0];
	light_rgb[1] = world->light->color[1];
	light_rgb[2] = world->light->color[2];
	return (light_rgb);
}
