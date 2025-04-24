/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:21:54 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/24 16:34:02 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_object	**get_objects(t_input_data **data)
{
	int			num_of_objs;
	int			i;
	t_object	**objects;

	num_of_objs = get_no_obj_elems(data);
	objects = (t_object **)ft_calloc(sizeof(t_object *), num_of_objs + 1);
	if (!objects)
		return (NULL);
	i = -1;
	num_of_objs = 0;
	while (data[++i])
	{
		if (!ft_strncmp(data[i]->id, "A\0", 2) || !ft_strncmp(data[i]->id,
				"C\0", 2) || !ft_strncmp(data[i]->id, "L\0", 2))
			continue ;
		else
			objects[num_of_objs++] = assign_object(data[i]);
	}
	return (objects);
}

t_camera	*get_cam_data(t_input_data **data)
{
	int			i;
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	i = -1;
	while (data[++i])
	{
		if (!ft_strncmp(data[i]->id, "C\0", 2))
		{
			cam->fov = (double)(M_PI / 180 * data[i]->fov);
			cam->orientation_vector = data[i]->orientation_vector;
			cam->orientation_vector[3] = 0;
			cam->origin = data[i]->coords;
			cam->origin[3] = 1;
			assign_pixel_size(cam);
			load_camera_transform_matrix(cam);
			return (cam);
		}
	}
	return (NULL);
}

t_light	**get_light_data(t_input_data **data)
{
	int		i;
	t_light	**lights;
	int		no_lights;

	no_lights = get_no_light_elems(data);
	lights = (t_light **)malloc((no_lights + 1) * sizeof(t_light *));
	lights[no_lights] = NULL;
	i = -1;
	no_lights = 0;
	while (data[++i])
	{
		if (!ft_strncmp(data[i]->id, "L\0", 2))
		{
			lights[no_lights] = (t_light *)malloc(sizeof(t_light));
			if (!lights[no_lights])
				return (NULL);
			lights[no_lights]->brightness = data[i]->brightness;
			lights[no_lights]->color = init_tuple((double)data[i]->color[0],
					(double)data[i]->color[1], (double)data[i]->color[2], 1);
			free(data[i]->color);
			lights[no_lights]->coords = data[i]->coords;
			lights[no_lights++]->coords[3] = 1;
		}
	}
	return (lights);
}

t_ambient	*get_ambient_data(t_input_data **data)
{
	int			i;
	t_ambient	*ambient;

	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	if (!ambient)
		return (NULL);
	i = -1;
	while (data[++i])
	{
		if (!ft_strncmp(data[i]->id, "A\0", 2))
		{
			ambient->brightness = data[i]->ambient_light_ratio;
			ambient->color = init_tuple((double)data[i]->color[0],
					(double)data[i]->color[1], (double)data[i]->color[2], 1);
			free(data[i]->color);
			return (ambient);
		}
	}
	return (NULL);
}
