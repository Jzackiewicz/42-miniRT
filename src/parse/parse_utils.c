/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:43:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/11 13:26:01 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	init_with_default(t_object *obj)
{
	obj->id = NULL;
	obj->ambient_light_ratio = 0.0;
	obj->orientation_vector = NULL;
	obj->fov = 0;
	obj->brightness = 0;
	obj->diameter = 0;
	obj->height = 0;
	obj->colors = NULL;
	obj->cords = NULL;
	obj->vector = NULL;
	obj->height = 0;
}

void	parse_colors(char *colors, t_object *obj)
{
	char	**colors_split;

	obj->colors = ft_calloc(4, sizeof(int));
	if (!obj->colors)
		return ;
	colors_split = ft_split(colors, ',');
	if (!colors_split)
		return ;
	obj->colors[0] = ft_atoi(colors_split[0]);
	obj->colors[1] = ft_atoi(colors_split[1]);
	obj->colors[2] = ft_atoi(colors_split[2]);
	ft_arr2d_free(colors_split);
}

void	parse_vector(char *vector, t_object *obj)
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

void	parse_cords(char *cords, t_object *obj)
{
	char	**cords_split;

	obj->cords = ft_calloc(4, sizeof(double));
	if (!obj->cords)
		return ;
	cords_split = ft_split(cords, ',');
	if (!cords_split)
		return ;
	obj->cords[0] = ft_atof(cords_split[0]);
	obj->cords[1] = ft_atof(cords_split[1]);
	obj->cords[2] = ft_atof(cords_split[2]);
	ft_arr2d_free(cords_split);
}

void	free_object(t_object *obj)
{
	if (obj)
	{
		if (obj->id)
			free(obj->id);
		if (obj->orientation_vector)
			free(obj->orientation_vector);
		if (obj->colors)
			free(obj->colors);
		if (obj->cords)
			free(obj->cords);
		if (obj->vector)
			free(obj->vector);
	}
}

// void	print_object(t_object *obj)
// {
// 	if (!obj)
// 	{
// 		printf("Error: Object is NULL\n");
// 		return ;
// 	}
// 	if (obj->id)
// 		printf("id: %s\n", obj->id);
// 	printf("ambient_light_ratio: %f\n", obj->ambient_light_ratio);
// 	if (obj->orientation_vector)
// 		printf("orientation_vector: %f %f %f\n", obj->orientation_vector[0],
// 			obj->orientation_vector[1], obj->orientation_vector[2]);
// 	printf("fov: %d\n", obj->fov);
// 	printf("brightness: %f\n", obj->brightness);
// 	printf("diameter: %f\n", obj->diameter);
// 	printf("height: %f\n", obj->height);
// 	if (obj->colors)
// 		printf("colors: %d %d %d\n", obj->colors[0], obj->colors[1],
// 			obj->colors[2]);
// 	if (obj->cords)
// 		printf("cords: %f %f %f\n", obj->cords[0], obj->cords[1],
// 			obj->cords[2]);
// 	if (obj->vector)
// 		printf("vector: %f %f %f\n", obj->vector[0], obj->vector[1],
// 			obj->vector[2]);
// 	printf("height: %f\n", obj->height);
// }
