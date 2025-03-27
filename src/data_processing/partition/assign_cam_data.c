/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cam_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:37:54 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/27 20:19:56 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/* calculates the pixel_size and assigns inside of the t_camera structure.
 *  assigns also the attributes: half_width & half_height */
void	assign_pixel_size(t_camera *cam_data)
{
	double	half_view;
	double	aspect;

	half_view = tan(cam_data->fov / 2.0);
	aspect = (double)WINDOW_HEIGHT / (double)WINDOW_WIDTH;
	if (aspect >= 1)
	{
		cam_data->half_width = half_view;
		cam_data->half_height = half_view / aspect;
	}
	else
	{
		cam_data->half_width = half_view * aspect;
		cam_data->half_height = half_view;
	}
	cam_data->pixel_size = (cam_data->half_width * 2.0) / (double)WINDOW_HEIGHT;
}

static t_matrix	*assign_data_to_matrix(double *cam_left, double *cam_up,
		double *forward)
{
	t_matrix	*orient_matrix;

	orient_matrix = init_matrix(4, 4);
	make_identity(orient_matrix);
	orient_matrix->grid[0][0] = cam_left[0];
	orient_matrix->grid[0][1] = cam_left[1];
	orient_matrix->grid[0][2] = cam_left[2];
	orient_matrix->grid[1][0] = cam_up[0];
	orient_matrix->grid[1][1] = cam_up[1];
	orient_matrix->grid[1][2] = cam_up[2];
	orient_matrix->grid[2][0] = -forward[0];
	orient_matrix->grid[2][1] = -forward[1];
	orient_matrix->grid[2][2] = -forward[2];
	return (orient_matrix);
}

static t_matrix	*get_orient_matrix(t_camera *cam_data)
{
	t_matrix	*orient_matrix;
	double		*global_up;
	double		*cam_left;
	double		*cam_up;
	double		*tmp;

	global_up = init_tuple(0);
	global_up[0] = 1;
	normalize(&global_up);
	cam_left = cross(cam_data->orientation_vector, global_up);
	free(global_up);
	if (compare_floats(cam_data->orientation_vector[1], 1)
		|| compare_floats(cam_data->orientation_vector[1], -1))
		cam_left[0] = -1;
	cam_up = cross(cam_left, cam_data->orientation_vector);
	orient_matrix = assign_data_to_matrix(cam_left, cam_up,
			cam_data->orientation_vector);
	free(cam_left);
	free(cam_up);
	return (orient_matrix);
}

void	load_camera_transform_matrix(t_camera *cam_data)
{
	t_matrix	*orient_matrix;
	t_matrix	*trans_matrix;
	double		*tmp;

	tmp = negate_tuple(cam_data->origin);
	trans_matrix = translation(tmp);
	free(tmp);
	orient_matrix = get_orient_matrix(cam_data);
	cam_data->transform = multiply_matrices(orient_matrix, trans_matrix);
	cam_data->inv_transform = inverse(cam_data->transform);
	free_matrix(orient_matrix);
	free_matrix(trans_matrix);
	free_matrix(cam_data->transform);
}
