/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/17 19:31:59 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"


/* func should return a 2d array (bitmap) of hitpoints to color in mlx */
double **generate_bitmap(t_intersec **ray_intersections)
{
    int i;
	double bitmap[WINDOW_WIDTH][WINDOW_HEIGHT];
	double **hitpoint;
	double *pos;

	i = 0;
	while (ray_intersections[i])
	{
		hitpoint = identify_hit(ray_intersections[i]);
		i++;
	}
}