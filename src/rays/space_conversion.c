/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/28 13:35:18 by jzackiew         ###   ########.fr       */
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
