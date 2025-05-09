/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:32:02 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/22 15:46:28 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

static void	parse_sphere(t_input_data *obj, char **line_split)
{
	parse_coords(line_split[1], obj);
	obj->diameter = ft_atof(line_split[2]);
	parse_colors(line_split[3], obj);
	if (line_split[4] && !check_for_overflow(line_split[4])
		&& ft_atoi(line_split[4]) == 1)
		obj->is_checkered = true;
	else
		obj->is_checkered = false;
	if (line_split[5])
	{
		if (line_split[5][ft_strlen(line_split[5]) - 1] == '\n')
			line_split[5][ft_strlen(line_split[5]) - 1] = '\0';
		obj->texture_path = ft_strdup(line_split[5]);
	}
	else
		obj->texture_path = NULL;
}

static void	parse_plane(t_input_data *obj, char **line_split)
{
	parse_coords(line_split[1], obj);
	parse_vector(line_split[2], obj);
	parse_colors(line_split[3], obj);
	if (line_split[4] && !check_for_overflow(line_split[4])
		&& ft_atoi(line_split[4]) == 1)
		obj->is_checkered = true;
	else
		obj->is_checkered = false;
	if (line_split[5])
	{
		if (line_split[5][ft_strlen(line_split[5]) - 1] == '\n')
			line_split[5][ft_strlen(line_split[5]) - 1] = '\0';
		obj->texture_path = ft_strdup(line_split[5]);
	}
	else
		obj->texture_path = NULL;
}

static void	parse_cylinder_or_cone(t_input_data *obj, char **line_split)
{
	parse_coords(line_split[1], obj);
	parse_vector(line_split[2], obj);
	obj->diameter = ft_atof(line_split[3]);
	obj->height = ft_atof(line_split[4]);
	parse_colors(line_split[5], obj);
	if (line_split[6] && !check_for_overflow(line_split[6])
		&& ft_atoi(line_split[6]) == 1)
		obj->is_checkered = true;
	else
		obj->is_checkered = false;
	if (line_split[7])
	{
		if (line_split[7][ft_strlen(line_split[7]) - 1] == '\n')
			line_split[7][ft_strlen(line_split[7]) - 1] = '\0';
		obj->texture_path = ft_strdup(line_split[7]);
	}
	else
		obj->texture_path = NULL;
}

void	parse_objects(char **line_split, t_input_data **objects, int i)
{
	objects[i] = malloc(sizeof(t_input_data));
	if (!objects[i])
		return ;
	init_with_default(objects[i]);
	objects[i]->id = ft_strdup(line_split[0]);
	if (!ft_strncmp(objects[i]->id, "sp\0", 3))
		parse_sphere(objects[i], line_split);
	else if (!ft_strncmp(objects[i]->id, "pl\0", 3))
		parse_plane(objects[i], line_split);
	else if (!ft_strncmp(objects[i]->id, "cy\0", 3)
		|| !ft_strncmp(objects[i]->id, "co\0", 3))
		parse_cylinder_or_cone(objects[i], line_split);
}
