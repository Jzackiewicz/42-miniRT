/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:10:12 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/14 11:58:52 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/parser.h"

static void	parse_ambient(t_input_data *obj, char **line_split)
{
	obj->ambient_light_ratio = ft_atof(line_split[1]);
	parse_colors(line_split[2], obj);
}

static void	parse_camera(t_input_data *obj, char **line_split)
{
	char	**orientation_split;

	parse_coords(line_split[1], obj);
	obj->orientation_vector = ft_calloc(4, sizeof(double));
	if (!obj->orientation_vector)
		return ;
	orientation_split = ft_split(line_split[2], ',');
	if (!orientation_split)
		return ;
	obj->orientation_vector[0] = ft_atof(orientation_split[0]);
	obj->orientation_vector[1] = ft_atof(orientation_split[1]);
	obj->orientation_vector[2] = ft_atof(orientation_split[2]);
	ft_arr2d_free(orientation_split);
	obj->fov = ft_atoi(line_split[3]);
}

static void	parse_light(t_input_data *obj, char **line_split)
{
	parse_coords(line_split[1], obj);
	obj->brightness = ft_atof(line_split[2]);
	parse_colors(line_split[3], obj);
}

void	parse_settings(char **line_split, t_input_data **objects, int i)
{
	objects[i] = malloc(sizeof(t_input_data));
	if (!objects[i])
		return ;
	init_with_default(objects[i]);
	objects[i]->id = ft_strdup(line_split[0]);
	if (!ft_strncmp(objects[i]->id, "A\0", 2))
		parse_ambient(objects[i], line_split);
	else if (!ft_strncmp(objects[i]->id, "C\0", 2))
		parse_camera(objects[i], line_split);
	else if (!ft_strncmp(objects[i]->id, "L\0", 2))
		parse_light(objects[i], line_split);
}
