/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bitmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:02:53 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/21 18:54:17 by agarbacz         ###   ########.fr       */
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

	bitmap = (int **)malloc(sizeof(int *) * WINDOW_WIDTH * WINDOW_HEIGHT);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		bitmap[i] = (int *)malloc(sizeof(int) * WINDOW_HEIGHT);
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
