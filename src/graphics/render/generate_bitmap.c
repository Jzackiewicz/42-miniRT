/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/24 13:12:23 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"
#include "../../../inc/rays.h"

int	rgb_to_int(double r, double g, double b)
{
	int	color;

	color = 0;
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

	bitmap = (int **)malloc(sizeof(int *) * WINDOW_WIDTH);
	if (!bitmap)
		return (NULL);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		bitmap[i] = (int *)malloc(sizeof(int) * WINDOW_HEIGHT);
		if (!bitmap[i])
			return (NULL);
		j = 0;
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
int	**generate_bitmap(t_intersec ***ray_intersections, t_ray **rays,
		t_camera *cam_data)
{
	int i;
	int **bitmap;
	t_intersec *hitpoint;
	double *pos;
	double width;
	double pixel_size;

	bitmap = init_bitmap();
	i = 0;
	width = get_canvas_width(cam_data);
	// printf("width: %f\n", width);
	pixel_size = WINDOW_WIDTH / width;
	while (ray_intersections[i])
	{
		hitpoint = identify_hit(ray_intersections[i]);
		if (hitpoint)
		{
			pos = position(rays[i], hitpoint->t);
			// print_tuple(pos);
			// print_tuple(cam_data->orientation_vector);
			// exit(1);
			int	x_pos = (int)((pos[0] * pixel_size) + (WINDOW_WIDTH / 2)); 
			int	y_pos = (int)((pos[1] * pixel_size) + (WINDOW_HEIGHT / 2));
			free(pos);
			int	color = rgb_to_int(hitpoint->object->color[0], hitpoint->object->color[1], hitpoint->object->color[2]);
			bitmap[x_pos][y_pos] = color;
		}
		i++;
	}
	return (bitmap);
}

int	**generate_new_bitmap(t_camera *cam_data, t_object **objs)
{
	int wall_z = 100;
	int wall_size = 70;
	double	pixel_size = wall_size / WINDOW_WIDTH;
	double	half = wall_size / 2;
	double	world_y;
	double	world_x;
	int	i;
	int	j;
	
	int **bitmap = init_bitmap();
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		world_y = half - pixel_size * i;
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			world_x = -half + pixel_size * j;
			double	tmp[] = {world_x, world_y, wall_z, 1};
			double	*dir = subtract_tuple(tmp, cam_data->origin);
			normalize(&dir);
			t_ray *ray = create_ray(cam_data->origin, dir);
			t_intersec **intersex = get_sorted_intersections(ray, objs);
			t_intersec *hitpoint = identify_hit(intersex);
			// printf("hitpoint: %f\n", hitpoint->t);
			if (hitpoint)
			{
				printf("t: %f\n", hitpoint->t);
				bitmap[j][i] = rgb_to_int(objs[0]->color[0], objs[0]->color[1], objs[0]->color[2]);
			}

		}
	}
	return(bitmap);
}