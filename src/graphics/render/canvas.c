/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:34:11 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 11:45:09 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"
#include "../../../inc/miniRT.h"

double	get_canvas_width(t_camera *cam_data)
{
	double	distance;
	double	*cam_to_center;
	double	center[4];
	double	angle;
	double	width;
	
	center[0] = 0.0;
	center[1] = 0.0;
	center[2] = 0.0;
	center[3] = 0.0;
	cam_to_center = subtract_tuple(cam_data->origin, center);
	distance = magnitude(cam_to_center);
	angle = cam_data->fov * (M_PI / 180.0);
	width = 2 * (tan(angle / 2) * distance);
	return (width);
}
