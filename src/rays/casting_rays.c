/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/17 17:02:19 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"
#include "../../inc/miniRT.h"

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
	printf("distance: %f\nangle: %f\nwidth: %f\n", distance, angle, width);
	return (width);
}
/* Not sure if works */
double	*get_cam_orientation_vector(t_camera *cam_data, int h_id, int w_id)
{
	double	width;
	double	angle[2];
	double	*direction;	
	double	ratio;
	t_matrix	*tmp;
	
	angle[0] = cam_data->fov * (M_PI / 180) / 2;
	ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	angle[1] = angle[0] * ratio;
	angle[0] *= (w_id - WINDOW_WIDTH / 2) / (double)WINDOW_WIDTH;
	angle[1] *= (h_id - WINDOW_HEIGHT / 2) / (double)WINDOW_HEIGHT;
	tmp = rotation_x(angle[0]);
	direction = multiply_matrix_and_tuple(tmp, cam_data->orientation_vector);
	free(tmp);
	tmp = rotation_y(angle[1]);
	direction = multiply_matrix_and_tuple(tmp, direction);
	free(tmp);
	return (direction);
}

t_ray	**generate_rays(t_camera *cam_data)
{
	int	i;
	int	j;
	double	width;
	double	*direction;
	t_ray	**rays;
	
	width = get_canvas_width(cam_data);
	rays = (t_ray **)malloc(sizeof(t_ray *) * WINDOW_WIDTH * WINDOW_HEIGHT);
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			rays[i * WINDOW_WIDTH + j] = (t_ray *)malloc (sizeof(t_ray));
			if (!rays[i * WINDOW_WIDTH + j])
				return (NULL);
			direction = get_cam_orientation_vector(cam_data, i, j);
			rays[i * WINDOW_WIDTH + j] = create_ray(cam_data->origin, direction);
		}
	}
	return (rays);
}
