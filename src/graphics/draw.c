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

void	draw_pixel(t_ray_tracer_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > WINDOW_WIDTH || y > WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->mlx_data->img_addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void	draw_image(t_ray_tracer_data *data)
{
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->window_ptr,
		data->mlx_data->img_ptr, 0, 0);
}

