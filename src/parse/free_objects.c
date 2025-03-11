/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:09:46 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/11 14:40:50 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

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

void	free_objects(t_object **objs, int no_objects)
{
	while (--no_objects != -1)
	{
		free_object(objs[no_objects]);
		free(objs[no_objects]);
	}
	free(objs);
}