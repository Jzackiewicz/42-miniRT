/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/02 18:37:46 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"
#include "../../inc/miniRT.h"

/* For now for sphere only */
t_ray	*ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_ray	*new_ray;
	
	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray || !obj->transform)
		return (NULL);
	new_ray->origin = init_tuple(1);
	new_ray->direction = init_tuple(0);
	if (!new_ray->origin || !new_ray->direction)
		return (NULL);
	new_ray->origin = multiply_tuple_and_matrix(obj->inv_transform, ray->origin);
	new_ray->direction = multiply_tuple_and_matrix(obj->inv_transform, ray->direction);
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
	if (!ray)
		return (NULL);
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
