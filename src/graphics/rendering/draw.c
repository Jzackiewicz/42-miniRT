/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kubaz <kubaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:30:12 by agarbacz          #+#    #+#             */
/*   Updated: 2025/05/02 00:54:20 by kubaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"

/* draws a pixel on specified coordinates with a specified color */
static void	draw_pixel(t_ray_tracer_data *data, int x, int y, int color)
{
	char	*dst;

	if (y > WINDOW_WIDTH || x > WINDOW_HEIGHT || x < 0 || y < 0)
		return ;
	dst = data->mlx_data->img_addr + (x * data->mlx_data->line_length + y
			* (data->mlx_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render_image(t_ray_tracer_data *data, int **bitmap)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			draw_pixel(data, i, j, bitmap[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_data->mlx_ptr, data->mlx_data->window_ptr,
		data->mlx_data->img_ptr, 0, 0);
}
