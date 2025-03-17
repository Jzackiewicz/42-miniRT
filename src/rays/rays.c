/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/17 12:06:17 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

t_ray	*create_ray(double *origin, double *direction)
{
	t_ray	*new_ray;

	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->origin = origin;
	new_ray->direction = direction;
	new_ray->t = 0;
	return (new_ray);
}

double	*position(t_ray *ray, double t)
{
	double	*dir_t;
	double	*pos;

	dir_t = multiply_tuple(ray->direction, t);
	pos = add_tuple(ray->origin, dir_t);
	free(dir_t);
	return (pos);
}

static t_input_data	*find_camera(t_input_data **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!ft_strncmp(data[i]->id, "C\0", 2))
			return (data[i]);
		i++;
	}
	return (NULL);
}
