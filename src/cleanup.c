/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:35:09 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 12:33:16 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void clean_rays(t_ray **rays)
{
	int i;

	i = 0;
	while (rays[i])
	{
		free(rays[i]->direction);
		free(rays[i]);
	}
	free(rays);
}

void	clean_intersections(t_intersec ***ray_intersex)
{
	int	i;
	int j;
	
	i = 0;
	while (ray_intersex[i])
	{
		j = 0;
		while (ray_intersex[i][j])
		{
			free(ray_intersex[i][j]);
			j++;
		}
		free(ray_intersex[i]);
		i++;
	}
	free(ray_intersex);
}
void	clean_objects(t_object **objs, t_input_data **data, int no_lines)
{
	free_objects(data, no_lines);
	for (int i = 0; objs[i]; i++)
		free(objs[i]);
	free(objs);
}
