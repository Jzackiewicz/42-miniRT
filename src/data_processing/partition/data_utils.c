/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:33:06 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/22 17:31:04 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"
#include "../../../inc/miniRT.h"

void	free_input_data(t_input_data **inp_data, int no_lines)
{
	while (--no_lines != -1)
		free(inp_data[no_lines]);
	free(inp_data);
}

static void	free_object(t_object *obj, t_ray_tracer_data *rt_data)
{
	free(obj->color);
	free(obj->coords);
	free(obj->id);
	free(obj->texture_path);
	free(obj->orientation_vector);
	free_matrix(obj->inv_transform);
	free_matrix(obj->transform);
	free_texture(rt_data, obj);
	free(obj);
}

static void	free_lights(t_world *world)
{
	int	i;

	i = -1;
	while (world->lights[++i])
	{
		free(world->lights[i]->color);
		free(world->lights[i]->coords);
		free(world->lights[i]);
	}
	free(world->lights);
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
	free_lights(world);
}

void	free_world(t_world *world, t_ray_tracer_data *rt_data)
{
	int	i;

	free_settings(world);
	i = 0;
	while (world->objs[i])
	{
		free_object(world->objs[i], rt_data);
		i++;
	}
	free(world->objs);
	free(world);
}
