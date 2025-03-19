/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/19 11:04:13 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/rays.h"
#include "../../../inc/miniRT.h"

/* Finds t for ray-sphere intersection for identity sphere */
double	*intersect_sphere(t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	coefficients[3];
	double	delta;
	double	*coords;
	
	coords = init_tuple(1);
	oc_vector = subtract_tuple(ray->origin, coords);
	normalize(&oc_vector);
	free(coords);
	coefficients[0] = dot(ray->direction, ray->direction);
	coefficients[1] = dot(oc_vector, ray->direction) * 2;
	coefficients[2] = dot(oc_vector, oc_vector) - 1;
	free(oc_vector);
	delta = pow(coefficients[1], 2) - 4 * coefficients[0] * coefficients[2];
	if (delta < 0)
		return (NULL);
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = (-coefficients[1] + sqrt(delta)) / (2 * coefficients[0]);
	arr_t[1] = (-coefficients[1] - sqrt(delta)) / (2 * coefficients[0]);
	return (arr_t);
}

double	*intersect_plane(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	denom;
	double	t;
	double	*sub;

	denom = dot(ray->direction, obj->orientation_vector);
	if (compare_floats(denom, 0.0))
		return (NULL);
	sub = subtract_tuple(obj->coords, ray->origin);
	t = dot(obj->orientation_vector, sub) / denom;
	free(sub);
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = t;
	arr_t[1] = t;
	return (arr_t);
}

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
	transform = multiply_matrices(translation_transform, scaling_transform);
	free_matrix(scaling_transform);
	free_matrix(translation_transform);
	new_ray->origin = multiply_matrix_and_tuple(transform, ray->origin);
	
	return (new_ray);
}

/* highest level intersection finding function
	called with a pointer to an object (plane, sphere or cylinder)
	and an initialized t_ray pointer */
double	*intersect(t_object *obj, t_ray *ray)
{
	double	*arr_t;

	arr_t = NULL;
	if (!ft_strncmp(obj->id, "sp\0", 3))
	{
		arr_t = intersect_sphere(ray);
		// obj->transform = ray_to_object_space(obj);
		
	}
	else if (!ft_strncmp(obj->id, "pl\0", 3))
		arr_t = intersect_plane(obj, ray);
	else
	{
		printf("Error: unknown object id: %s\n", obj->id);
		return (NULL);
	}
	return (arr_t);
}
