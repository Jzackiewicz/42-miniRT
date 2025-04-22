/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/22 13:09:15 by agarbacz         ###   ########.fr       */
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
	t_uv	uv;
	int		int_color;

	if (comps->obj->is_checkered)
		rbg_color = get_checkered_color(comps->obj, comps->point);
	else if (comps->obj->texture)
	{
		if (0 == ft_strncmp(comps->obj->id, "sp\0", 3))
			uv = get_spherical_map(comps);
		else if (0 == ft_strncmp(comps->obj->id, "pl\0", 3))
			uv = get_planar_map(comps);
		else if (0 == ft_strncmp(comps->obj->id, "cy\0", 3))
			uv = get_cylindrical_map(comps);
		rbg_color = get_texture_color(comps->obj->texture, uv.u, uv.v);
	}
	else
		rbg_color = tupledup(comps->obj->color, 3);
	res = apply_phong_attributes(world, comps, rbg_color);
	free(rbg_color);
	int_color = rgb_to_int(res);
	free(res);
	return (int_color);
}
