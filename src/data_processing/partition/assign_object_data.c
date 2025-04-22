/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/22 17:22:13 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

t_matrix	*get_plane_rotation_matrix(t_object *obj)
{
	t_matrix	*rotation_transform;
	t_matrix	*matrix_x;
	t_matrix	*matrix_z;
	double		denom;

	denom = sqrt(pow(obj->orientation_vector[1], 2)
			+ pow(obj->orientation_vector[2], 2));
	if (compare_floats(denom, 0))
		matrix_x = rotation_x(0);
	else
		matrix_x = rotation_x(acos(obj->orientation_vector[1] / denom));
	denom = sqrt(pow(obj->orientation_vector[1], 2)
			+ pow(obj->orientation_vector[0], 2));
	if (compare_floats(denom, 0))
		matrix_z = rotation_z(0);
	else
		matrix_z = rotation_z(acos(obj->orientation_vector[1] / denom));
	rotation_transform = multiply_matrices(matrix_x, matrix_z);
	free_matrix(matrix_x);
	free_matrix(matrix_z);
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
		tmp_2 = get_plane_rotation_matrix(obj);
	else
		tmp_2 = create_identity_matrix(4, 4);
	if (obj->height && obj->diameter)
		tmp_3 = scaling(obj->diameter, obj->height, obj->diameter);
	else if (!obj->height && obj->diameter)
		tmp_3 = scaling(obj->diameter, obj->diameter, obj->diameter);
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
	obj->color = convert_color(data->color);
	obj->coords = data->coords;
	obj->orientation_vector = data->vector;
	obj->is_checkered = data->is_checkered;
	obj->texture_path = (char *)data->texture_path;
	obj->texture = NULL;
	obj->transform = get_transform_matrix(obj);
	obj->inv_transform = inverse(obj->transform);
	return (obj);
}
