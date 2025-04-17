/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/17 17:01:23 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

static t_matrix	*prepare_sphere_transform(t_object *obj)
{
	t_matrix	*scaling_transform;
	t_matrix	*translation_transform;
	t_matrix	*transform;
	double		tmp[3];

	tmp[0] = obj->diameter;
	tmp[1] = obj->diameter;
	tmp[2] = obj->diameter;
	scaling_transform = scaling(tmp);
	transpose(&scaling_transform);
	translation_transform = translation(obj->coords);
	transform = multiply_matrices(translation_transform, scaling_transform);
	free_matrix(scaling_transform);
	free_matrix(translation_transform);
	return (transform);
}

static t_matrix	*get_plane_rotation_matrix(t_object *obj)
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

static t_matrix	*prepare_plane_transform(t_object *obj)
{
	t_matrix	*transform;
	t_matrix	*rotation_transform;
	t_matrix	*translation_transform;

	rotation_transform = get_plane_rotation_matrix(obj);
	translation_transform = translation(obj->coords);
	transform = multiply_matrices(translation_transform, rotation_transform);
	free_matrix(rotation_transform);
	free_matrix(translation_transform);
	return (transform);
}

t_matrix	*prepare_cylinder_transform(t_object *obj)
{
	// t_matrix	*scaling_transform;
	t_matrix	*translation_transform;
	// t_matrix	*transform;
	// double		tmp[3];
	
	// tmp[0] = obj->diameter;
	// tmp[1] = obj->diameter;
	// tmp[2] = obj->diameter;
	translation_transform = translation(obj->coords);
	return (translation_transform);
}

static void	load_object_transform_matrix(t_object *obj)
{
	t_matrix	*transform;

	if (!strncmp(obj->id, "sp\0", 3))
		transform = prepare_sphere_transform(obj);
	else if (!strncmp(obj->id, "pl\0", 3))
		transform = prepare_plane_transform(obj);
	else if (!strncmp(obj->id, "cy\0", 3))
		transform = prepare_cylinder_transform(obj);
	else
	{
		transform = init_matrix(4, 4);
		make_identity(transform);
	}
	obj->transform = transform;
	obj->inv_transform = inverse(transform);
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
	load_object_transform_matrix(obj);
	return (obj);
}
