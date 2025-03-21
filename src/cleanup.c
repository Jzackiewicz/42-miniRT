/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:35:09 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 13:12:08 by agarbacz         ###   ########.fr       */
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
		i++;
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

void	free_bitmap(int **bitmap)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		free(bitmap[i]);
		i++;
	}
	free(bitmap);
}
