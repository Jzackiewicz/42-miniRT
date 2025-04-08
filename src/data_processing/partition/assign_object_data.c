/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_object_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/08 18:45:30 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

static t_matrix	*prepare_sphere_transoform(t_object *obj)
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

static t_matrix	*prepare_plane_transform(t_object *obj)
{
	t_matrix	*transform;
	double		angle_x;
	double		angle_z;
	double		denom;

	denom = sqrt(pow(obj->orientation_vector[1], 2) + pow(obj->orientation_vector[2], 2));
	if (compare_floats(denom, 0))
		angle_x = 0;
	else
		angle_x = obj->orientation_vector[1] / denom;
	denom = sqrt(pow(obj->orientation_vector[0], 2) + pow(obj->orientation_vector[1], 2));
	if (compare_floats(denom, 0))
		angle_z = 0;
	else
		angle_z = obj->orientation_vector[1] / denom;
	angle_x = M_PI / 2;
	angle_z = 0;
	printf("angle x: %f\n", angle_x / M_PI * 180);
	printf("angle z: %f\n", angle_z / M_PI * 180);
	transform = multiply_matrices(rotation_x(angle_x), rotation_z(angle_z));
	return (transform);
}

static void	load_object_transform_matrix(t_object *obj)
{
	t_matrix	*transform;

	if (!strncmp(obj->id, "sp\0", 3))
		transform = prepare_sphere_transoform(obj);
	else if (!strncmp(obj->id, "pl\0", 3))
		transform = prepare_plane_transform(obj);
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
	load_object_transform_matrix(obj);
	return (obj);
}
