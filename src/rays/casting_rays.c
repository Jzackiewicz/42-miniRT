/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/28 13:59:35 by jzackiew         ###   ########.fr       */
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

t_ray *ray_for_pixel(t_camera *cam_data, int px, int py)
{
	double	offset[2];
	double	*world_point;
	double	*pixel_point;
	double	*zero_point;
	t_ray	*ray;
	
	ray = (t_ray *)malloc(sizeof(t_ray));
	offset[0] = ((double)px + 0.5) * cam_data->pixel_size;
	offset[1] = ((double)py + 0.5) * cam_data->pixel_size;
	zero_point = init_tuple(1);
	world_point = init_tuple(1);
	world_point[0] = cam_data->half_height - offset[0];
	world_point[1] = cam_data->half_width - offset[1];
	world_point[2] = -1;
	pixel_point = multiply_tuple_and_matrix(cam_data->inv_transform, world_point);
	ray->origin = multiply_tuple_and_matrix(cam_data->inv_transform, zero_point);
	ray->direction = subtract_tuple(pixel_point, ray->origin);
	normalize(&ray->direction);
	free(world_point);
	free(zero_point);
	free(pixel_point);
	return (ray);
}

void	free_ray(t_ray *ray)
{
	free(ray->origin);
	free(ray->direction);
	free(ray);
}
