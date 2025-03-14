/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:09:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/14 11:59:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/parser.h"

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
void	free_objects(t_input_data **objs, int no_objects)
{
	while (--no_objects != -1)
	{
		free_object(objs[no_objects]);
		free(objs[no_objects]);
	}
	free(objs);
}
