/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:57:27 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/09 19:31:49 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

int	lighting(t_world *world, t_comps *comps)
{
	return (apply_phong_model(world, comps));
	// if (is_shadowed(world, comps->over_point))
	// 	return (apply_shadow(comps, world));
	// else
	// 	return (apply_phong_model(world, comps));
}
