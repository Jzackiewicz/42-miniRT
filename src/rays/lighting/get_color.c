/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/14 13:41:17 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static int	rgb_to_int(double *rgb)
{
	rgb[0] = fmin(255, fmax(0, rgb[0]));
	rgb[1] = fmin(255, fmax(0, rgb[1]));
	rgb[2] = fmin(255, fmax(0, rgb[2]));
	return (((int)rgb[0] << 16) | ((int)rgb[1] << 8) | (int)rgb[2]);
}

int	get_pixel_color(t_world *world, t_comps *comps)
{
	double	*res;
	double	*rbg_color;
	int		int_color;

	if (comps->obj->is_checkered)
		rbg_color = get_checkered_color(comps->obj, comps->point);
	else
		rbg_color = tupledup(comps->obj->color, 3);
	res = apply_phong_attributes(world, comps, rbg_color);
	free(rbg_color);
	int_color = rgb_to_int(res);
	free(res);
	return (int_color);
}
