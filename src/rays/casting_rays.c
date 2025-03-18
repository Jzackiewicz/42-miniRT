/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/18 12:41:24 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "../../inc/rays.h"

/* Not sure if works */
static double	*get_cam_orientation_vector(t_camera *cam_data, int h_id, int w_id)
{
	double		angle[2];
	double		*direction;
	double		ratio;
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

t_ray	**generate_rays(t_camera *cam_data)
{
	int		i;
	int		j;
	double	*direction;
	// double	*tmp;
	t_ray	**rays;

	rays = (t_ray **)ft_calloc(WINDOW_WIDTH * WINDOW_HEIGHT + 1, sizeof(t_ray *));
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			// rays[i * WINDOW_WIDTH + j] = (t_ray *)malloc(sizeof(t_ray));
			// if (!rays[i * WINDOW_WIDTH + j])
			// 	return (NULL);
			direction = get_cam_orientation_vector(cam_data, i, j);
			// free(tmp);
			// direction = normalize(tmp);
			rays[i * WINDOW_WIDTH + j] = create_ray(cam_data->origin,
					direction);
		}
	}
	return (rays);
}
