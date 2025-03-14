/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 09:27:02 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

double	*intersect_sphere(t_input_data *obj, t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	b;
	double	c;
	double	delta;

	oc_vector = substract_tuple(ray->origin, obj->coords);
	b = dot(oc_vector, ray->direction) * 2;
	c = dot(oc_vector, oc_vector) - pow(obj->diameter / 2, 2);
	free(oc_vector);
	delta = pow(b, 2) - 4 * c;
	if (delta < 0)
		return (NULL);
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = (-b + sqrt(delta)) / 2;
	arr_t[1] = (-b - sqrt(delta)) / 2;
	return (arr_t);
}

double	*intersect_plane(t_input_data *obj, t_ray *ray)
{
	double	*arr_t;
	double	denom;
	double	t;

	denom = dot(ray->direction, obj->vector);
	if (compare_floats(denom, 0.0))
		return (NULL);
	t = dot(obj->vector, substract_tuple(obj->coords, ray->origin)) / denom;
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = t;
	arr_t[1] = t;
	return (arr_t);
}

/* highest level intersection finding function
	called with a pointer to an object (plane, sphere or cylinder)
	and an initialized t_ray pointer */
double	*intersect(t_input_data *obj, t_ray *ray)
{
	double	*arr_t;

	arr_t = NULL;
	if (!ft_strncmp(obj->id, "sp\0", 3))
		arr_t = intersect_sphere(obj, ray);
	else if (!ft_strncmp(obj->id, "pl\0", 3))
		arr_t = intersect_plane(obj, ray);
	else if (!ft_strncmp(obj->id, "cy\0", 3))
		arr_t = intersect_cylinder(obj, ray);
	else
	{
		printf("Error: unknown object id: %s\n", obj->id);
		return (NULL);
	}
	return (arr_t);
}

void	append_intersec(t_intersec **all, double *arr_t, t_input_data *obj,
		int intersec_no)
{
	t_intersec *x;
	int i;

	if (!arr_t || !all || !obj)
		return ;
	x = (t_intersec *)malloc(sizeof(t_intersec));
	if (!x)
		return ;
	i = 0;
	while (i < 2)
	{
		x->t = arr_t[i];
		x->object = obj;
		all[i + intersec_no] = x;
		i++;
	}
}