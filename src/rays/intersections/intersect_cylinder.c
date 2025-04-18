/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:09:22 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/19 00:26:32 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"
#include "../../../inc/rays.h"

static double	*truncate_cylinder(double *arr_t, t_ray *ray, double cyl_height)
{
	bool	is_t[2];
	int		i;
	double	*out_t;

	i = -1;
	while (++i < 2)
	{
		if (ray->origin[1] + arr_t[i] * ray->direction[1] > - cyl_height / 2 && ray->origin[1]
			+ arr_t[i] * ray->direction[1] < cyl_height / 2)
			is_t[i] = true;
		else
			is_t[i] = false;
	}
	if (!is_t[0] && !is_t[1])
		return (free(arr_t), NULL);
	out_t = tupledup(arr_t, 2);
	if (is_t[0] && !is_t[1])
		out_t[1] = arr_t[0];
	else if (is_t[1] && !is_t[0])
		out_t[0] = arr_t[1];
	free(arr_t);
	return (out_t);
}

static double	*truncate_caps(t_ray *ray, double *arr_t, double diameter)
{
	int		i;
	double	x;
	double	z;
	double	is_t[2];
	double	*out_t;

	i = -1;
	while (++i < 2)
	{
		x = ray->origin[0] + arr_t[i] * ray->direction[0];
		z = ray->origin[2] + arr_t[i] * ray->direction[2];
		if (pow(x, 2) + pow(z, 2) < diameter || compare_floats(pow(x, 2)
				+ pow(z, 2), diameter))
			is_t[i] = true;
		else
			is_t[i] = false;
	}
	out_t = tupledup(arr_t, 2);
	if (!is_t[0] && !is_t[1])
		return (free(arr_t), free(out_t), NULL);
	if (is_t[0] && !is_t[1])
		out_t[1] = arr_t[0];
	else if (is_t[1] && !is_t[0])
		out_t[0] = arr_t[1];
	return (free(arr_t), out_t);
}

static double	*intersect_caps(double *arr_t, t_ray *ray, double cyl_height)
{
	double	*out_t;
	
	if (compare_floats(ray->direction[1], 0) || (arr_t
			&& !compare_floats(arr_t[0], arr_t[1])))
		return (arr_t);
	out_t = (double *)malloc(sizeof(double) * 2);
	out_t[0] = (-cyl_height / 2 - ray->origin[1]) / ray->direction[1];
	out_t[1] = (cyl_height / 2 - ray->origin[1]) / ray->direction[1];
	if (arr_t && arr_t[0] < out_t[0])
		out_t[0] = arr_t[0];
	if (arr_t && arr_t[1] < out_t[1])
		out_t[1] = arr_t[1];
	if (arr_t && arr_t[1] < out_t[0])
		out_t[0] = arr_t[1];
	if (arr_t && arr_t[0] < out_t[1])
		out_t[1] = arr_t[0];
	free(arr_t);
	return (out_t);
}

static double	*intersect_infinite_tube(t_ray *ray, double diameter)
{
	double	coefficients[3];
	double	delta;
	double	*arr_t;

	coefficients[0] = pow(ray->direction[0], 2) + pow(ray->direction[2], 2);
	if (compare_floats(coefficients[0], 0))
		return (NULL);
	coefficients[1] = 2 * ray->origin[0] * ray->direction[0] + 2
		* ray->origin[2] * ray->direction[2];
	coefficients[2] = pow(ray->origin[0], 2) + pow(ray->origin[2], 2)
		- diameter;
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

/* Finds t for ray-cylinder intersection for a closed cylinder.
Intersected cylinder is a cylinder that is already translated and scaled by
parameters in obj argument.*/
double	*intersect_cylinder(t_ray *ray, t_object *obj)
{
	double	*arr_t;

	obj->diameter = 1;
	obj->height = 1;
	arr_t = intersect_infinite_tube(ray, obj->diameter);
	if (arr_t)
		arr_t = truncate_cylinder(arr_t, ray, obj->height);
	arr_t = intersect_caps(arr_t, ray, obj->height);
	if (arr_t)
		arr_t = truncate_caps(ray, arr_t, obj->diameter);
	return (arr_t);
}
