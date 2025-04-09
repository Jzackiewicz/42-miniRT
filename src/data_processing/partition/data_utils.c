/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:33:06 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/09 12:48:11 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

double	*convert_color(int *int_color)
{
	double	*color;

	color = (double *)malloc(sizeof(double) * 3);
	if (!color)
		return (NULL);
	color[0] = (double)int_color[0];
	color[1] = (double)int_color[1];
	color[2] = (double)int_color[2];
	free(int_color);
	return (color);
}

void	free_input_data(t_input_data **inp_data, int no_lines)
{
	while (--no_lines != -1)
		free(inp_data[no_lines]);
	free(inp_data);
}

static void	free_object(t_object *obj)
{
	free(obj->color);
	free(obj->coords);
	free(obj->id);
	free(obj->orientation_vector);
	free_matrix(obj->inv_transform);
	free_matrix(obj->transform);
	free(obj);
}

static void	free_settings(t_world *world)
{
	free(world->ambient->color);
	free(world->ambient);
	free_matrix(world->camera->inv_transform);
	free_matrix(world->camera->transform);
	free(world->camera->orientation_vector);
	free(world->camera->origin);
	free(world->camera);
	free(world->light->color);
	free(world->light->coords);
	free(world->light);
}

void	free_world(t_world *world)
{
	int	i;

	free_settings(world);
	i = 0;
	while (world->objs[i])
	{
		free_object(world->objs[i]);
		i++;
	}
	free(world->objs);
	free(world);
}
