/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:21:32 by jzackiew          #+#    #+#             */
/*   Updated: 2025/05/02 00:45:42 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/rays.h"

t_ray	*ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_ray	*new_ray;

	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray || !obj->transform)
		return (NULL);
	new_ray->origin = multiply_tuple_and_matrix(obj->inv_transform,
			ray->origin);
	new_ray->direction = multiply_tuple_and_matrix(obj->inv_transform,
			ray->direction);
	return (new_ray);
}

t_ray	*ray_for_pixel(t_camera *cam_data, int px, int py)
{
	double	offset[2];
	double	*worldp;
	double	*pixel_point;
	double	*zero_point;
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	offset[0] = ((double)px + 0.5) * cam_data->pixel_size;
	offset[1] = ((double)py + 0.5) * cam_data->pixel_size;
	zero_point = init_tuple(0, 0, 0, 1);
	worldp = init_tuple(cam_data->half_width - offset[0], cam_data->half_height
			- offset[1], -1, 1);
	pixel_point = multiply_tuple_and_matrix(cam_data->inv_transform, worldp);
	ray->origin = multiply_tuple_and_matrix(cam_data->inv_transform,
			zero_point);
	ray->direction = subtract_tuple(pixel_point, ray->origin);
	normalize(&ray->direction);
	free(worldp);
	free(zero_point);
	free(pixel_point);
	return (ray);
}

int	color_at(t_world *world, t_ray *ray)
{
	t_intersec	**intersections;
	t_intersec	*hit;
	t_comps		*comps;
	double		result;

	result = 0;
	intersections = get_sorted_intersections(ray, world->objs);
	hit = identify_hit(intersections);
	if (hit)
	{
		comps = prepare_computations(hit, ray);
		free(hit);
		result = get_pixel_color(world, comps);
		free_comps(comps);
	}
	else
		result = 0;
	free_intersections(intersections);
	return (result);
}
