/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/25 11:59:36 by jzackiew         ###   ########.fr       */
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
