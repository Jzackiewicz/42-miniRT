/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:18:32 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/24 14:21:15 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/**
	a set of functions that map a point on a sphere to a UV coordinate.

	@param comps: which encapsulate
	a point in 3D space (in object-space coordinates)

	The functions map it to a UV coordinate for planes, cylinders and spheres.
	The mapping is done by calculating the spherical coordinates of the point
	and then converting them to UV coordinates. The UV coordinates
	range from 0 to 1.
	returns t_uv structure containing the UV coordinates of the point.
 */

// @var obj_point, a point in object's local space, not in world's coords
t_uv	get_planar_map(t_comps *comps)
{
	t_uv	uv;
	double	*obj_point;

	obj_point = multiply_tuple_and_matrix(comps->obj->inv_transform,
			comps->point);
	if (!obj_point)
	{
		uv.u = 0;
		uv.v = 0;
		return (uv);
	}
	uv.u = fabs(fmod(obj_point[0], 1.0));
	uv.v = fabs(fmod(obj_point[2], 1.0));
	free(obj_point);
	return (uv);
}

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
	uv.v = (phi / M_PI);
	return (uv);
}

t_uv	get_cylindrical_map(t_comps *comps)
{
	t_uv	uv;
	double	theta;
	double	*obj_pt;
	double	height;

	obj_pt = multiply_tuple_and_matrix(comps->obj->inv_transform, comps->point);
	if (!obj_pt)
	{
		uv.u = 0;
		uv.v = 0;
		return (uv);
	}
	theta = atan2(obj_pt[0], obj_pt[2]);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	height = obj_pt[1];
	if (comps->obj->height > 0)
		uv.v = fmod(height / comps->obj->height + 0.5, 1.0);
	else
		uv.v = fmod(height + 0.5, 1.0);
	if (uv.u < 0)
		uv.u += 1.0;
	if (uv.v < 0)
		uv.v += 1.0;
	free(obj_pt);
	return (uv);
}

t_uv	get_cone_map(t_comps *comps)
{
	t_uv	uv;
	double	theta;
	double	radius;
	double	*obj_pt;
	double	height;

	obj_pt = multiply_tuple_and_matrix(comps->obj->inv_transform, comps->point);
	if (!obj_pt)
		return (uv.u = 0, uv.v = 0, uv);
	theta = atan2(obj_pt[0], obj_pt[2]);
	uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
	height = obj_pt[1];
	radius = sqrt(obj_pt[0] * obj_pt[0] + obj_pt[2] * obj_pt[2]);
	if (comps->obj->height > 0)
		uv.v = height / comps->obj->height;
	else
		uv.v = height;
	if (uv.u < 0)
		uv.u += 1.0;
	if (uv.v < 0)
		uv.v += 1.0;
	if (uv.v > 1.0)
		uv.v = fmod(uv.v, 1.0);
	return (free(obj_pt), uv);
}
