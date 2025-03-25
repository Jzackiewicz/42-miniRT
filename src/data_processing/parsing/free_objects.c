/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:09:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 13:06:18 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

// frees the freeable contents of the object
void	free_object(t_input_data *obj)
{
	if (obj)
	{
		if (obj->id)
			free(obj->id);
		if (obj->orientation_vector)
			free(obj->orientation_vector);
		if (obj->color)
			free(obj->color);
		if (obj->coords)
			free(obj->coords);
		if (obj->vector)
			free(obj->vector);
	}
}

// no_objects is neccessary for proper free() calls
void	free_objects(t_input_data **inp_data, t_object **objs, int no_lines)
{
	int	i;

	while (--no_lines != -1)
	{
		free_object(inp_data[no_lines]);
		free(inp_data[no_lines]);
	}
	free(inp_data);
	i = 0;
	while (objs[i])
	{
		free(objs[i]);
		i++;
	}
	free(objs);
}
