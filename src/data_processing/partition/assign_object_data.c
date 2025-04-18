/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/19 00:25:28 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

static t_matrix *prepare_sphere_transform(t_object *obj)
{
	t_matrix *scaling_transform;
	t_matrix *translation_transform;
	t_matrix *transform;

	scaling_transform = scaling(obj->diameter, obj->diameter, obj->diameter);
	transpose(&scaling_transform);
	translation_transform = translation(obj->coords);
	transform = multiply_matrices(translation_transform, scaling_transform);
	free_matrix(scaling_transform);
	free_matrix(translation_transform);
	return (transform);
}

t_matrix	*get_rotation_matrix(double *orient_vector)
{
	t_matrix	*rotation_matrix;
	t_matrix	*x_rot_matrix;
	t_matrix	*y_rot_matrix;
	t_matrix	*z_rot_matrix;
	double		angles[4];
	

	angles[0] = acos(orient_vector[0]) - M_PI / 2;
	angles[1] =	acos(orient_vector[1]) - M_PI / 2;
	angles[2] = acos(orient_vector[2]) - M_PI / 2;
	printf("x: %f, y: %f, z: %f\n", angles[0] / M_PI * 180, angles[1] / M_PI * 180, angles[2] / M_PI * 180);
	x_rot_matrix = rotation_x(angles[0]);
	y_rot_matrix = rotation_y(angles[1]);
	z_rot_matrix = rotation_z(angles[2]);
	rotation_matrix = multiply_matrices(z_rot_matrix, y_rot_matrix);
	free(z_rot_matrix);
	free(y_rot_matrix);
	z_rot_matrix = rotation_matrix;
	z_rot_matrix = multiply_matrices(rotation_matrix, x_rot_matrix);
	free(rotation_matrix);
	free(x_rot_matrix);
	rotation_matrix = z_rot_matrix;
	return (rotation_matrix);
}

t_matrix *get_plane_rotation_matrix(t_object *obj)
{
	t_matrix *rotation_transform;
	t_matrix *matrix_x;
	t_matrix *matrix_z;
	double denom;

	denom = sqrt(pow(obj->orientation_vector[1], 2) + pow(obj->orientation_vector[2], 2));
	if (compare_floats(denom, 0))
		matrix_x = rotation_x(0);
	else
		matrix_x = rotation_x(acos(obj->orientation_vector[1] / denom));
	denom = sqrt(pow(obj->orientation_vector[1], 2) + pow(obj->orientation_vector[0], 2));
	if (compare_floats(denom, 0))
		matrix_z = rotation_z(0);
	else
		matrix_z = rotation_z(acos(obj->orientation_vector[1] / denom));
	rotation_transform = multiply_matrices(matrix_x, matrix_z);
	free_matrix(matrix_x);
	free_matrix(matrix_z);
	print_matrix(rotation_transform);
	return (rotation_transform);
}

static t_matrix *prepare_plane_transform(t_object *obj)
{
	t_matrix *transform;
	t_matrix *rotation_transform;
	t_matrix *translation_transform;

	rotation_transform = get_plane_rotation_matrix(obj);
	translation_transform = translation(obj->coords);
	transform = multiply_matrices(translation_transform, rotation_transform);
	free_matrix(rotation_transform);
	free_matrix(translation_transform);
	return (transform);
}

t_matrix *prepare_cylinder_transform(t_object *obj)
{
	t_matrix *translation_transform;

	translation_transform = translation(obj->coords);
	return (translation_transform);
}

t_matrix	*get_transform_matrix(t_object *obj)
{
	t_matrix	*transform;
	t_matrix	*tmp_1;
	t_matrix	*tmp_2;
	t_matrix	*tmp_3;
	
	tmp_1 = translation(obj->coords);
	// if (obj->orientation_vector)
	// 	tmp_2 = get_rotation_matrix(obj->orientation_vector);
	// else
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

void load_object_transform_matrix(t_object *obj)
{
	t_matrix *transform;

	if (!strncmp(obj->id, "sp\0", 3))
		transform = prepare_sphere_transform(obj);
	else if (!strncmp(obj->id, "pl\0", 3))
		transform = prepare_plane_transform(obj);
	else if (!strncmp(obj->id, "cy\0", 3))
		transform = prepare_cylinder_transform(obj);
	else
		transform = create_identity_matrix(4, 4);
	obj->transform = transform;
	obj->inv_transform = inverse(transform);
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
	load_object_transform_matrix(obj);
	// obj->transform = get_transform_matrix(obj);
	// obj->inv_transform = inverse(obj->transform);
	return (obj);
}
