/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/25 11:59:36 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/rays.h"

t_ray	*create_ray(double *origin, double *direction)
{
	t_ray	*new_ray;

	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->origin = origin;
	new_ray->direction = direction;
	return (new_ray);
}

/* p. 104 from the bible... i mean book */
t_ray *ray_for_pixel(t_camera *cam_data, int px, int py)
{
	double x_offset = (px + 0.5) * cam_data->pixel_size;
	double y_offset = (py + 0.5) * cam_data->pixel_size;
	double world_x = cam_data->half_width - x_offset;
	double world_y = cam_data->half_height - y_offset;
	// double pixel = inverse(cam_data->transform);
	// double origin;
	// double direction;
}