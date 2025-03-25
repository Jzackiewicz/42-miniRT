/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:43:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 12:08:30 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

void	init_with_default(t_input_data *obj)
{
	obj->id = NULL;
	obj->ambient_light_ratio = 0.0;
	obj->orientation_vector = NULL;
	obj->fov = 0;
	obj->brightness = 0;
	obj->diameter = 0;
	obj->height = 0;
	obj->color = NULL;
	obj->coords = NULL;
	obj->vector = NULL;
	obj->height = 0;
}

void	parse_colors(char *color, t_input_data *obj)
{
	char	**colors_split;

	obj->color = ft_calloc(4, sizeof(int));
	if (!obj->color)
		return ;
	colors_split = ft_split(color, ',');
	if (!colors_split)
		return ;
	obj->color[0] = ft_atoi(colors_split[0]);
	obj->color[1] = ft_atoi(colors_split[1]);
	obj->color[2] = ft_atoi(colors_split[2]);
	ft_arr2d_free(colors_split);
}

void	parse_vector(char *vector, t_input_data *obj)
{
	char	**vector_split;

	obj->vector = ft_calloc(4, sizeof(double));
	if (!obj->vector)
		return ;
	vector_split = ft_split(vector, ',');
	if (!vector_split)
		return ;
	obj->vector[0] = ft_atof(vector_split[0]);
	obj->vector[1] = ft_atof(vector_split[1]);
	obj->vector[2] = ft_atof(vector_split[2]);
	ft_arr2d_free(vector_split);
}

void	parse_coords(char *coords, t_input_data *obj)
{
	char	**coords_split;

	obj->coords = ft_calloc(4, sizeof(double));
	if (!obj->coords)
		return ;
	coords_split = ft_split(coords, ',');
	if (!coords_split)
		return ;
	obj->coords[0] = ft_atof(coords_split[0]);
	obj->coords[1] = ft_atof(coords_split[1]);
	obj->coords[2] = ft_atof(coords_split[2]);
	ft_arr2d_free(coords_split);
}

void	print_object(t_input_data *obj)
{
	if (!obj)
	{
		printf("Error: Object is NULL\n");
		return ;
	}
	if (obj->id)
		printf("id: %s\n", obj->id);
	printf("ambient_light_ratio: %f\n", obj->ambient_light_ratio);
	if (obj->orientation_vector)
		printf("orientation_vector: %f %f %f\n", obj->orientation_vector[0],
			obj->orientation_vector[1], obj->orientation_vector[2]);
	printf("fov: %d\n", obj->fov);
	printf("brightness: %f\n", obj->brightness);
	printf("diameter: %f\n", obj->diameter);
	printf("height: %f\n", obj->height);
	if (obj->color)
		printf("color: %d %d %d\n", obj->color[0], obj->color[1],
			obj->color[2]);
	if (obj->coords)
		printf("coords: %f %f %f\n", obj->coords[0], obj->coords[1],
			obj->coords[2]);
	if (obj->vector)
		printf("vector: %f %f %f\n", obj->vector[0], obj->vector[1],
			obj->vector[2]);
	printf("height: %f\n", obj->height);
}
