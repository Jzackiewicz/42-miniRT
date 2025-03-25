/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 11:39:04 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"
#include "../../../inc/rays.h"

int	rgb_to_int(double r, double g, double b)
{
	r = fmin(255, fmax(0, r));
	g = fmin(255, fmax(0, g));
	b = fmin(255, fmax(0, b));
	return (((int)r << 16) | ((int)g << 8) | (int)b);
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
		t_camera *cam_data, t_light *light)
{
	int			i;
	int			**bitmap;
	t_intersec	*hitpoint;
	double		*pos;
	double		width;
	double		pixel_size;
	double		light_color;
	double		*normal;
	int			x_pos;
	int			y_pos;
	int			color;

	bitmap = init_bitmap();
	i = 0;
	width = get_canvas_width(cam_data);
	pixel_size = WINDOW_WIDTH / width;
	while (ray_intersections[i]) {
		hitpoint = identify_hit(ray_intersections[i]);
		if (hitpoint)
		{
			pos = position(rays[i], hitpoint->t);
			normal = get_normal_at((hitpoint->object), pos);
			light_color = lighting(light, hitpoint->object, cam_data, normal,
					pos);
			x_pos = (int)((pos[0] * pixel_size) + (WINDOW_WIDTH / 2));
			y_pos = (int)((pos[1] * pixel_size) + (WINDOW_HEIGHT / 2));
			free(pos);
			bitmap[x_pos][y_pos] = light_color;
		}
		i++;
	}
	return (bitmap);	
}

int	get_lightning_color(t_camera *cam_data, t_light *light_data, t_ray *ray, t_intersec *hitpoint)
{
	int	light_color;
	double	*pos;
	double	*normal;

	pos = position(ray, hitpoint->t);
	normal = get_normal_at((hitpoint->object), pos);
	light_color = lighting(light_data, hitpoint->object, cam_data, normal, pos);

	return (light_color);
}

int	**generate_new_bitmap(t_camera *cam_data, t_object **objs, t_light *light_data)
{
	double wall_z = 10.0;
	double wall_size = 10.0;
	double	pixel_size;
	double	half;
	double	world_y;
	double	world_x;
	int	i;
	int	j;
	
	int **bitmap = init_bitmap();
	i = -1;
	pixel_size = wall_size / WINDOW_WIDTH;
	half = wall_size / 2;
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
			//ray = ray_to_object_space(ray, objs[0]);
			t_intersec **intersex = get_sorted_intersections(ray, objs);
			t_intersec *hitpoint = identify_hit(intersex);
			

			if (hitpoint)
			{
				int color = get_lightning_color(cam_data, light_data, ray, hitpoint);
				bitmap[i][j] = color;
			}
		}
	}
	return(bitmap);
}



