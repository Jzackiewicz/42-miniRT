/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/25 12:20:57 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

// TODO: AMBIENT DOESN'T WORK
void	assign_object_material(t_ambient *ambient, t_object *obj)
{
	obj->material = (t_material *)malloc(sizeof(t_material));
	if (!obj->material)
		return ;
	obj->material->ambient = ambient->brightness;
	obj->material->diffuse = 0.9;
	obj->material->specular = 0.9;
	obj->material->shininess = 32;
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
	obj->color = data->color;
	obj->coords = data->coords;
	obj->orientation_vector = data->orientation_vector;
	load_transform_matrix(obj);
	return (obj);
}
