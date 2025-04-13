/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 16:22:11 by jzackiew         ###   ########.fr       */
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

int	lighting(t_world *world, t_comps *comps)
{
	double	*res;
	double	*new_color;
	int		int_final_color;

	new_color = get_checker_color(comps);
	res = apply_phong_attributes(world, comps, new_color);
	int_final_color = rgb_to_int(res);
	free(res);
	return (int_final_color);
}
