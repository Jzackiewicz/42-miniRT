/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/12 15:07:34 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

double	*intersect_sphere(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	b;
	double	c;
	double	delta;
	
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	oc_vector = substract_tuple(ray->origin, obj->cords);
	b = dot(oc_vector, ray->direction) * 2;
	c = dot(oc_vector, oc_vector) - pow(obj->diameter / 2, 2);
	free(oc_vector);
	delta = pow(b, 2) - 4 * c;
	if (delta < 0)
	{
		printf("Does not intersect\n");
		exit(-1);
	}
	arr_t[0] = (-b + sqrt(delta)) / 2;
	arr_t[1] = (-b - sqrt(delta)) / 2;
	return (arr_t);
}

double	*intersect(t_object *obj, t_ray *ray)
{
	double *arr_t;

	arr_t = NULL;
	if (!ft_strncmp(obj->id, "sp\0", 3))
		arr_t = intersect_sphere(obj, ray);
	return (arr_t);
}
