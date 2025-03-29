/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/28 15:33:50 by jzackiew         ###   ########.fr       */
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
	int			i;
	int			j;
	int			**bitmap;
	t_ray		*ray;
	t_intersec	**intersex;
	t_intersec	*hitpoint;
	t_world		*world;
	int			color;

	bitmap = init_bitmap();
	world = create_world(cam_data, light_data, ambient_data, objs);
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = -1;
		while (++j < WINDOW_WIDTH)
		{
			ray = ray_for_pixel(cam_data, i, j);
			color = color_at(world, ray);
			bitmap[i][j] = color;
		}
	}
	return (bitmap);
}
