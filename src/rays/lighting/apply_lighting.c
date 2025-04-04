/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/04 20:01:57 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

double	lighting(t_world *world, t_comps *comps)
{
	if (is_shadowed(world, comps->over_point))
		return (apply_shadow(comps, world));
	else
		return (apply_phong_model(world, comps));
}
