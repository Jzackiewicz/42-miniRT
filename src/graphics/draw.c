/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:30:12 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/13 16:33:00 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/graphics.h"

/* draws a pixel on specified coordinates with a specified color */
void	draw_pixel(t_ray_tracer_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > WINDOW_WIDTH || y > WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->mlx_data->img_addr + (y * data->mlx_data->line_length + x
			* (data->mlx_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*  health check debug draw */
static void draw_rectangle(t_ray_tracer_data *data, int color)
{
    int x;
    int y;

    y = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            draw_pixel(data, x, y, color);
            x++;
        }
        y++;
    }
}

/*
 	to find out what x and y will be
	will this be an array?
	will this be a reversed doubly linked binary tree?
	will this be a toyota corolla 2024?
	only kuab knows.......
	for health check the fn now draws a rectangle :33
*/
void	trace_rays(t_ray_tracer_data *data) 
{
	/* ideal world pseudocode
	x, y = calc_rays()
	draw_pixel(data, x, y, color) */
	draw_rectangle(data, 0x00CCCC);
}

void	render_image(t_ray_tracer_data *data)
{
	trace_rays(data);
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->window_ptr,
		data->mlx_data->img_ptr, 0, 0);
}

