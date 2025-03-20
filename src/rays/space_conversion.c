/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:07:59 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/20 16:17:58 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"
#include "../../inc/miniRT.h"

void	load_transform_matrix(t_object *obj)
{
	t_matrix	*scaling_transform;
	t_matrix	*translation_transform;
	t_matrix	*transform;
	double		tmp[3];

	tmp[0] = obj->diameter;
	tmp[1] = obj->diameter;
	tmp[2] = obj->diameter;
	scaling_transform = scaling(tmp);
	translation_transform = translation(obj->coords);
	transform = multiply_matrices(translation_transform, scaling_transform);
	free_matrix(scaling_transform);
	free_matrix(translation_transform);
	obj->transform = transform;
	obj->inv_transform = inverse(transform);
}

/* For now for sphere only */
t_ray	*ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_ray	*new_ray;
	
	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray || !obj->transform)
		return (NULL);
	new_ray->origin = multiply_tuple_and_matrix(obj->inv_transform, ray->origin);
	new_ray->direction = multiply_tuple_and_matrix(obj->inv_transform, ray->direction);
	return (new_ray);
}
