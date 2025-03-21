/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:00:36 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/21 14:32:02 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"
#include "../../../inc/parser.h"

void	assign_object_material(t_ambient *ambient, t_object *obj)
{
	obj->material = (t_material *)malloc(sizeof(t_material));
	if (!obj->material)
		return ;
	obj->material->ambient = ambient->brightness * rgb_to_int(ambient->color[0],
			ambient->color[1], ambient->color[2]);
	obj->material->diffuse = 0.5;
	obj->material->specular = 0.5;
	obj->material->shininess = 0.5;
}

static t_object	*assign_object(t_input_data *data)
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

t_object	**get_objects(t_input_data **data, int no_data)
{
	int			num_of_objs;
	int			i;
	t_object	**objects;

	num_of_objs = no_data - 3;
	objects = (t_object **)ft_calloc(sizeof(t_object *), num_of_objs + 1);
	if (!objects)
		return (NULL);
	i = -1;
	num_of_objs = 0;
	while (++i < no_data)
	{
		if (!ft_strncmp(data[i]->id, "A\0", 2) || !ft_strncmp(data[i]->id,
				"C\0", 2) || !ft_strncmp(data[i]->id, "L\0", 2))
			continue ;
		else
			objects[num_of_objs++] = assign_object(data[i]);
	}
	return (objects);
}

t_camera	*get_cam_data(t_input_data **data, int no_data)
{
	int			i;
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	i = -1;
	while (++i < no_data)
	{
		if (!ft_strncmp(data[i]->id, "C\0", 2))
		{
			cam->fov = data[i]->fov;
			cam->orientation_vector = data[i]->orientation_vector;
			cam->origin = data[i]->coords;
			return (cam);
		}
	}
	return (NULL);
}

t_light	*get_light_data(t_input_data **data, int no_data)
{
	int		i;
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	i = -1;
	while (++i < no_data)
	{
		if (!ft_strncmp(data[i]->id, "L\0", 2))
		{
			light->brightness = data[i]->brightness;
			light->color = data[i]->color;
			light->coords = data[i]->coords;
			return (light);
		}
	}
	return (NULL);
}

t_ambient	*get_ambient_data(t_input_data **data, int no_data)
{
	int			i;
	t_ambient	*ambient;

	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient)
		return (NULL);
	i = -1;
	while (++i < no_data)
	{
		if (!ft_strncmp(data[i]->id, "A\0", 2))
		{
			ambient->brightness = data[i]->brightness;
			ambient->color = data[i]->color;
			return (ambient);
		}
	}
	return (NULL);
}

int	count_objects(t_object **objs)
{
	int	len;

	len = 0;
	while (objs[len])
		len++;
	return (len);
}
