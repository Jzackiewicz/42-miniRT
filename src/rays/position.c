/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/18 11:33:39 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

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

