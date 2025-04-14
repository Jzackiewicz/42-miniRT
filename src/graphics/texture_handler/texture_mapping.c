/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:18:32 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/14 17:24:14 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_uv get_spherical_map(t_comps *comps)
{
    t_uv uv;
    double theta;
    double phi;
    double normal_pt[3];  // Point in object space
    
    // Calculate object-space coordinates of intersection point
    // Subtract object center from intersection point
    normal_pt[0] = comps->point[0] - comps->obj->coords[0];
    normal_pt[1] = comps->point[1] - comps->obj->coords[1];
    normal_pt[2] = comps->point[2] - comps->obj->coords[2];
    
    // Normalize to get direction from center to surface (for sphere)
    double length = sqrt(normal_pt[0]*normal_pt[0] + 
                         normal_pt[1]*normal_pt[1] + 
                         normal_pt[2]*normal_pt[2]);
    
    normal_pt[0] /= length;
    normal_pt[1] /= length;
    normal_pt[2] /= length;
    
    // Calculate spherical coordinates
    theta = atan2(normal_pt[0], normal_pt[2]);
    phi = acos(normal_pt[1]);
    
    // Convert to UV coordinates
    uv.u = 1 - ((theta / (2 * M_PI)) + 0.5);
    uv.v = 1 - (phi / M_PI);
    
    return (uv);
}

