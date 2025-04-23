/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/23 18:24:37 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

static t_matrix *get_rotation_matrix(t_object *obj)
{
	t_matrix *rotation_transform;
	t_matrix *matrix_x;
	double	*axis;
	double	angle;
	double	*up_vector;
	t_matrix *matrix_y;
	t_matrix *matrix_z;
	t_matrix *tmp;

	up_vector = init_tuple(0, 1, 0, 0);
	axis = cross(obj->orientation_vector, up_vector);
	angle = acos(dot(obj->orientation_vector, up_vector));
	if (fabs(axis[0]) > EPSILON)
		matrix_x = rotation_x(angle);
	else
		matrix_x = create_identity_matrix(4, 4);
	if (fabs(axis[1]) > EPSILON)
		matrix_y = rotation_y(angle);
	else
		matrix_y = create_identity_matrix(4, 4);
	if (fabs(axis[2]) > EPSILON)
		matrix_z = rotation_z(angle);
	else
		matrix_z = create_identity_matrix(4, 4);
	tmp = multiply_matrices(matrix_z, matrix_y);
	rotation_transform = multiply_matrices(tmp, matrix_x);
	free_matrix(matrix_x);
	free_matrix(matrix_y);
	free_matrix(matrix_z);
	free_matrix(tmp);
	return (rotation_transform);
}

// static t_matrix *get_rotation_matrix(t_object *obj)
// {
// 	t_matrix *rotation_transform;
	
// 	printf("xangle: %f, yangle: %f, zangle: %f\n",  / M_PI * 180,  / M_PI * 180,  / M_PI * 180);
// 	(void)obj;
// 	exit(1);
// 	return (rotation_transform);
// }

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

t_object *assign_object(t_input_data *data)
{
	t_object *obj;

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
