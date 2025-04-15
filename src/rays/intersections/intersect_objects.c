/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:34:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/15 17:55:25 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"
#include "../../../inc/rays.h"

/* Finds t for ray-sphere intersection for identity sphere */
static double	*intersect_sphere(t_ray *ray)
{
	double	*arr_t;
	double	*oc_vector;
	double	coefficients[3];
	double	delta;
	double	*coords;

	coords = init_tuple(1);
	oc_vector = subtract_tuple(ray->origin, coords);
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
	arr_t[0] = (-coefficients[1] - sqrt(delta)) / (2 * coefficients[0]);
	arr_t[1] = (-coefficients[1] + sqrt(delta)) / (2 * coefficients[0]);
	return (arr_t);
}

/* Finds t for ray-plane intersection for identity plane.
Identity plane is a plane that intersects (0, 0, 0) world point and
has a (0, 0, 1) orientation vector */
static double	*intersect_plane(t_ray *ray)
{
	double	*arr_t;
	double	t;

	if (fabs(ray->direction[1]) < EPSILON)
		return (NULL);
	t = -ray->origin[1] / ray->direction[1];
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = t;
	arr_t[1] = t;
	return (arr_t);
}

double	*truncate_cylinder(double *arr_t, t_ray *ray, t_object *obj)
{
	double	limit;
	bool	is_t[2];
	int		i;
	double	*out_t;
	
	limit = obj->height / 2;
	i = -1;
	while (++i < 2)
	{
		if (arr_t[i] * ray->direction[1] > ray->origin[1] - limit &&
			arr_t[i] * ray->direction[1] < ray->origin[1] + limit)
			is_t[i] = true;
		else
			is_t[i] = false;
	}
	if (!is_t[0] && !is_t[1])
		return(free(arr_t), NULL);
	out_t = tupledup(arr_t, 2);
	if (is_t[0] && !is_t[1])
		out_t[1] = arr_t[0];
	else if (is_t[1] && !is_t[0])
		out_t[0] = arr_t[1];
	free(arr_t);
	return(out_t);
}

/* Finds t for ray-cylinder intersection for identity cylinder.
Identity cylinder is a cylinder that has it's center at (0, 0, 0) world point,
is infinitely long in +y and -y directions and it's radius length is 1*/
static	double	*intersect_cylinder(t_ray *ray)
{
	double	coefficients[3];
	double	delta;
	double	*arr_t;
	
	coefficients[0] = pow(ray->direction[0], 2) + pow(ray->direction[2], 2);
	if (compare_floats(coefficients[0], 0))
		return (NULL);
	coefficients[1] = 2 * ray->origin[0] * ray->direction[0] + 2 * ray->origin[2] * ray->direction[2];
	coefficients[2] = pow(ray->origin[0], 2) + pow(ray->origin[2], 2) - 1;
	delta = pow(coefficients[1], 2) - 4 * coefficients[0] * coefficients[2];
	if (delta < 0)
		return (NULL);
	arr_t = (double *)malloc(sizeof(double) * 2);
	if (!arr_t)
		return (NULL);
	arr_t[0] = (-coefficients[1] - sqrt(delta)) / (2 * coefficients[0]);
	arr_t[1] = (-coefficients[1] + sqrt(delta)) / (2 * coefficients[0]);
	return (arr_t);
}

/* highest level intersection finding function
	called with a pointer to an object (plane, sphere or cylinder)
	and an initialized t_ray pointer */
double	*intersect(t_object *obj, t_ray *ray)
{
	double	*arr_t;
	
	arr_t = NULL;
	if (!ft_strncmp(obj->id, "sp\0", 3))
		arr_t = intersect_sphere(ray);
	else if (!ft_strncmp(obj->id, "pl\0", 3))
		arr_t = intersect_plane(ray);
	else if (!ft_strncmp(obj->id, "cy\0", 3))
	{
		arr_t = intersect_cylinder(ray);
		if (arr_t)
			arr_t = truncate_cylinder(arr_t, ray, obj);
	}
	else
	{
		printf("Error: unknown object id: %s\n", obj->id);
		return (NULL);
	}
	return (arr_t);
}
