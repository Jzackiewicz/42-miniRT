/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:18:32 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/14 19:06:29 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

// TODO: planar and cylindrical maps

/**
	maps a point on a sphere to a UV coordinate.
	takes a point in 3D space (in object-space coordinates) and
	maps it to a UV coordinate for a sphere.
	The mapping is done by calculating the spherical coordinates of the point
	and then converting them to UV coordinates. The UV coordinates range from 0 to 1.
	returns t_uv structure containing the UV coordinates of the point.
 */
t_uv	get_spherical_map(t_comps *comps)
{
	t_uv	uv;
	double	theta;
	double	phi;
	double	normal_pt[3];
	double	length;

	normal_pt[0] = comps->point[0] - comps->obj->coords[0];
	normal_pt[1] = comps->point[1] - comps->obj->coords[1];
	normal_pt[2] = comps->point[2] - comps->obj->coords[2];
	length = sqrt(normal_pt[0] * normal_pt[0] + normal_pt[1] * normal_pt[1]
			+ normal_pt[2] * normal_pt[2]);
	normal_pt[0] /= length;
	normal_pt[1] /= length;
	normal_pt[2] /= length;
	theta = atan2(normal_pt[0], normal_pt[2]);
	phi = acos(normal_pt[1]);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	uv.v = 1 - (phi / M_PI);
	return (uv);
}
