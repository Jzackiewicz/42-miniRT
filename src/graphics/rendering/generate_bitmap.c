/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 13:43:02 by jzackiew         ###   ########.fr       */
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

static int	**init_bitmap(void)
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

int	get_lightning_color(t_camera *cam_data, t_light *light_data, t_ray *ray,
		t_intersec *hitpoint)
{
	int		light_color;
	double	*pos;
	double	*normal;

	pos = position(ray, hitpoint->t);
	normal = get_normal_at((hitpoint->object), pos);
	light_color = lighting(light_data, hitpoint->object, cam_data, normal, pos);
	return (light_color);
}

/* Temporary function just to show results. */
int	**generate_bitmap(t_camera *cam_data, t_object **objs,
		t_light *light_data, t_ambient *ambient_data)
{
	double		wall_z;
	double		wall_size;
	double		pixel_size;
	double		half;
	double		world_y;
	double		world_x;
	int			i;
	int			j;
	int			**bitmap;
	double		*dir;
	t_ray		*ray;
	t_intersec	**intersex;
	t_intersec	*hitpoint;
	int			color;

	wall_z = 10.0;
	wall_size = 10.0;
	bitmap = init_bitmap();
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
			double tmp[] = {world_x, world_y, wall_z, 1};
			dir = subtract_tuple(tmp, cam_data->origin);
			normalize(&dir);
			ray = create_ray(cam_data->origin, dir);
			// ray = ray_to_object_space(ray, objs[0]);
			intersex = get_sorted_intersections(ray, objs);
			// t_world	*world = create_world(cam_data, light_data, ambient_data, objs);
			// printf("%f\n", color_at(world, ray));
			hitpoint = identify_hit(intersex);
			if (hitpoint)
			{
				color = get_lightning_color(cam_data, light_data, ray,
						hitpoint);
				bitmap[i][j] = color;
			}
		}
	}
	return (bitmap);
}
