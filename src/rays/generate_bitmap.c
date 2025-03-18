/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/18 10:24:58 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"
#include "../../inc/miniRT.h"

int rgb_to_int(double r, double g, double b)
{
    int color = 0;
    color |= (int)(b);
    color |= (int)(g) << 8;
    color |= (int)(r) << 16;
    return (color);
}

int	**init_bitmap(void)
{
	int	i;
	int	j;
	int	**bitmap;

	bitmap = (int **)malloc(sizeof(int *) * WINDOW_WIDTH * WINDOW_HEIGHT);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		bitmap[i] = (int *)malloc(sizeof(int) * WINDOW_HEIGHT);
		while (j < WINDOW_HEIGHT)
		{
			bitmap[i][j] = 0;
			j++;
		}
		i++;
	}
	return (bitmap);
}

/* func should return a 2d array (bitmap) of hitpoints to color in mlx */
int **generate_bitmap(t_intersec ***ray_intersections, t_ray **rays, t_camera *cam_data)
{
    int i;
	int **bitmap;
	t_intersec *hitpoint;
	double *pos;
	double	width;
	double	ratio;
	
	bitmap = init_bitmap();
	i = 0;
	width = get_canvas_width(cam_data);
	ratio = WINDOW_WIDTH / width;
	printf("ratio: %f\n", ratio);
	while (ray_intersections[i])
	{
		hitpoint = identify_hit(ray_intersections[i]);
		if (hitpoint)
		{
			pos = position(rays[i], hitpoint->t);
			bitmap[(int)(pos[0] * ratio) + (WINDOW_WIDTH / 2)][(int)(pos[1] * ratio) + (WINDOW_HEIGHT / 2)] = rgb_to_int(hitpoint->object->color[0], hitpoint->object->color[1], hitpoint->object->color[2]);
			printf("x: %d, y: %d, color: %d\n", (int)(pos[0] * ratio) + (WINDOW_WIDTH / 2), (int)(pos[1] * ratio) + (WINDOW_HEIGHT / 2), rgb_to_int(hitpoint->object->color[0], hitpoint->object->color[1], hitpoint->object->color[2]));
			// printf("x: %d, y: %d\n", (int)(pos[0] * ratio) + (WINDOW_WIDTH / 2),(int)(pos[1] * ratio) + (WINDOW_HEIGHT / 2));
		}
		i++;
	}
	return (bitmap);
}