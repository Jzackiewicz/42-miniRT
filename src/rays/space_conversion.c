/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:07:59 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/20 13:06:53 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"
#include "../../inc/miniRT.h"

/* For now for sphere only */
t_ray	*ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_matrix	*scaling_transform;
	t_matrix	*translation_transform;
	t_matrix	*transform;
	t_ray		*new_ray;
	double		tmp[3];

	tmp[0] = obj->diameter;
	tmp[1] = obj->diameter;
	tmp[2] = obj->diameter;
	scaling_transform = scaling(tmp);
	translation_transform = translation(obj->coords);
	transform = multiply_matrices(scaling_transform, translation_transform);
	free_matrix(scaling_transform);
	free_matrix(translation_transform);
	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
/* 	printf("og matrix:\n");
	print_matrix(transform);
	inverse(transform);
	printf("inv matrix:\n");
	print_matrix(transform);
	printf("pre:\n");
	printf("origin: ");
	print_tuple(ray->origin);
	printf("dir: ");
	print_tuple(ray->direction); */
	inverse(transform);
	obj->transform = transform;
	new_ray->origin = multiply_tuple_and_matrix(transform, ray->origin);
	new_ray->direction = multiply_tuple_and_matrix(transform, ray->direction);
/* 	printf("\npost:\n");
	printf("origin: ");
	print_tuple(new_ray->origin);
	printf("dir: ");
	print_tuple(new_ray->direction); */
	//free_matrix(transform);
	// exit(1);
	return (new_ray);
}
