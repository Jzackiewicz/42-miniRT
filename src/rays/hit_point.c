/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:45:37 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/14 15:31:44 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

// i_s: intersections array sorted in ascending order
// returns NULL on non-negative t not found
double	*calc_hit_point(t_ray *ray, t_intersec **i_s)
{
	int i = 0;
	
	if (!i_s)
		return (NULL);
	while (i_s[i])
	{
		if (i_s[i]->t > 0)
			return (position(ray, i_s[i]->t));
		i++;
	}
	return (NULL);
}