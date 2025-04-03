/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/03 10:23:12 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/rays.h"

t_ray	*create_ray(double *origin, double *direction)
{
	t_ray	*new_ray;

	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->origin = origin;
	new_ray->direction = direction;
	return (new_ray);
}

double	*position(t_ray *ray, double t)
{
	double	*dir_t;
	double	*pos;

	dir_t = multiply_tuple(ray->direction, t);
	pos = add_tuple(ray->origin, dir_t);
	free(dir_t);
	pos[3] = 1;
	return (pos);
}

void	free_ray(t_ray *ray)
{
	free(ray->origin);
	free(ray->direction);
	free(ray);
}

void	free_intersections(t_intersec **ray_intersex)
{
	int	i;

	i = 0;
	while (ray_intersex[i])
	{
		free(ray_intersex[i]);
		i++;
	}
	free(ray_intersex);
}
