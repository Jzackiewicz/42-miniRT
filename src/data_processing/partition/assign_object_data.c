/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/05/02 02:43:23 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

static t_matrix	*get_rotation_matrix(t_object *obj)
{
	double		pitch;
	double		roll;
	t_matrix	*rotation_transform;
	t_matrix	*x_matrix;
	t_matrix	*z_matrix;

	pitch = atan2(-obj->orientation_vector[2],
			sqrt(pow(obj->orientation_vector[0], 2)
				+ pow(obj->orientation_vector[1], 2)));
	roll = -atan2(obj->orientation_vector[0], obj->orientation_vector[1]);
	x_matrix = rotation_x(pitch);
	z_matrix = rotation_z(roll);
	rotation_transform = multiply_matrices(z_matrix, x_matrix);
	free_matrix(x_matrix);
	free_matrix(z_matrix);
	return (rotation_transform);
}

t_matrix	*get_transform_matrix(t_object *obj)
{
	t_matrix	*transform;
	t_matrix	*tmp_1;
	t_matrix	*tmp_2;
	t_matrix	*tmp_3;

	tmp_1 = translation(obj->coords);
	if (obj->orientation_vector)
		tmp_2 = get_rotation_matrix(obj);
	else
		tmp_2 = create_identity_matrix(4, 4);
	if (obj->height && obj->diameter)
		tmp_3 = scaling(obj->diameter / 2, obj->height, obj->diameter / 2);
	else if (!obj->height && obj->diameter)
		tmp_3 = scaling(obj->diameter / 2, obj->diameter / 2, obj->diameter / 2);
	else
		tmp_3 = create_identity_matrix(4, 4);
	transform = multiply_matrices(tmp_1, tmp_2);
	free_matrix(tmp_1);
	free_matrix(tmp_2);
	tmp_1 = multiply_matrices(transform, tmp_3);
	free_matrix(transform);
	free_matrix(tmp_3);
	transform = tmp_1;
	return (transform);
}

t_object	*assign_object(t_input_data *data)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->id = data->id;
	obj->diameter = data->diameter;
	obj->height = data->height;
	obj->color = init_tuple((double)data->color[0], (double)data->color[1],
			(double)data->color[2], 1);
	free(data->color);
	obj->coords = data->coords;
	obj->orientation_vector = data->vector;
	obj->is_checkered = data->is_checkered;
	obj->texture_path = (char *)data->texture_path;
	obj->texture = NULL;
	obj->transform = get_transform_matrix(obj);
	obj->inv_transform = inverse(obj->transform);
	return (obj);
}
