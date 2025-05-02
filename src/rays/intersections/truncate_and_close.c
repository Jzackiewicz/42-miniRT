/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate_and_close.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:09:22 by jzackiew          #+#    #+#             */
/*   Updated: 2025/05/02 02:34:59 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"
#include "../../../inc/rays.h"

static double	*truncate_object(double *arr_t, t_ray *ray)
{
	bool	is_t[2];
	int		i;
	double	*out_t;

	i = -1;
	while (++i < 2)
	{
		if (arr_t[i] > 0 && ray->origin[1] + arr_t[i] * ray->direction[1] > -0.5
			&& ray->origin[1] + arr_t[i] * ray->direction[1] < 0.5)
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

static double	*intersect_caps(double *arr_t, t_ray *ray, char *obj_id)
{
	double	*out_t;

	if (compare_floats(ray->direction[1], 0.0) || (arr_t
			&& !compare_floats(arr_t[0], arr_t[1])))
		return (arr_t);
	out_t = (double *)malloc(sizeof(double) * 2);
	out_t[0] = (-0.5 - ray->origin[1]) / ray->direction[1];
	out_t[1] = out_t[0];
	if (!ft_strncmp(obj_id, "cy\0", 3))
		out_t[1] = (0.5 - ray->origin[1]) / ray->direction[1];
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

static double	*truncate_caps(t_ray *ray, double *arr_t)
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
		if (pow(x, 2) + pow(z, 2) < 1.0 || compare_floats(pow(x, 2) + pow(z, 2),
				1.0))
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

/* Finds t for ray-cylinder/cone intersection for 
	a closed identity cylinder/cone.
	Identity cylinder/cone is a cylinder/cone that is closed
	and 1 unit long and 1 unit wide.*/
double	*truncate_infinite_object(double *arr_t, t_ray *ray, char *obj_id)
{
	if (arr_t)
		arr_t = truncate_object(arr_t, ray);
	arr_t = intersect_caps(arr_t, ray, obj_id);
	if (arr_t)
		arr_t = truncate_caps(ray, arr_t);
	return (arr_t);
}
