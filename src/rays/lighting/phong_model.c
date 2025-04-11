/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:39:18 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/11 16:22:11 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static int	rgb_to_int(double *rgb)
{
	rgb[0] = fmin(255, fmax(0, rgb[0]));
	rgb[1] = fmin(255, fmax(0, rgb[1]));
	rgb[2] = fmin(255, fmax(0, rgb[2]));
	return (((int)rgb[0] << 16) | ((int)rgb[1] << 8) | (int)rgb[2]);
}

int	lighting(t_world *world, t_comps *comps)
{
	double	*res;
	int		color;

	res = apply_phong_attributes(world, comps);
	color = rgb_to_int(res);
	free(res);
	return (color);
}

// int apply_phong_model(t_world *world, t_comps *comps) {
//     double res[3];
//     double *effective_ambient;
//     double *effective_diffuse;
//     double *effective_specular;
//     double *obj_color;
//     double original_color[3];
    
// 	// store og color for later restore
//     original_color[0] = comps->obj->color[0];
//     original_color[1] = comps->obj->color[1];
//     original_color[2] = comps->obj->color[2];
    
//     if (true == comps->obj->is_checkered)
// 	{
//         obj_color = checker_at_object(comps->obj, comps->point);
//         if (obj_color)
// 		{
//             comps->obj->color[0] = obj_color[0];
//             comps->obj->color[1] = obj_color[1];
//             comps->obj->color[2] = obj_color[2];
//             free(obj_color);
//         }
//     }
//     effective_ambient = assign_effective_ambient(world, comps);
//     if (is_shadowed(world, comps->over_point))
// 	{
//         if (true == comps->obj->is_checkered) {
//             comps->obj->color[0] = original_color[0];
//             comps->obj->color[1] = original_color[1];
//             comps->obj->color[2] = original_color[2];
//         }
//         return (rgb_to_int(effective_ambient));
//     }
    
//     effective_diffuse = assign_effective_diffuse(world, comps);
//     effective_specular = assign_effective_specular(world, comps);
    
//     res[0] = fmin(255, effective_ambient[0] + effective_diffuse[0] + effective_specular[0]);
//     res[1] = fmin(255, effective_ambient[1] + effective_diffuse[1] + effective_specular[1]);
//     res[2] = fmin(255, effective_ambient[2] + effective_diffuse[2] + effective_specular[2]);
    
//     free(effective_ambient);
//     free(effective_diffuse);
//     free(effective_specular);
	
//     // reset color
//     if (true == comps->obj->is_checkered)
// 	{
//         comps->obj->color[0] = original_color[0];
//         comps->obj->color[1] = original_color[1];
//         comps->obj->color[2] = original_color[2];
//     }
//     return (rgb_to_int(res));
// }