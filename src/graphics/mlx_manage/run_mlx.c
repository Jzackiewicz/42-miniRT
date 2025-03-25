/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:56 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 12:26:03 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"
#include "../../../inc/miniRT.h"

static void	init_mlx(t_ray_tracer_data **rt_data)
{
	*rt_data = malloc(sizeof(t_ray_tracer_data));
	if (!(*rt_data))
		exit(1);
	(*rt_data)->mlx_data = malloc(sizeof(t_mlx_data));
	if (!(*rt_data)->mlx_data)
		exit(1);
	(*rt_data)->mlx_data->mlx_ptr = mlx_init();
	(*rt_data)->mlx_data->window_ptr = mlx_new_window((*rt_data)->mlx_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	(*rt_data)->mlx_data->img_ptr = mlx_new_image((*rt_data)->mlx_data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	(*rt_data)->mlx_data->img_addr = mlx_get_data_addr((*rt_data)->mlx_data->img_ptr,
			&(*rt_data)->mlx_data->bits_per_pixel,
			&(*rt_data)->mlx_data->line_length, &(*rt_data)->mlx_data->endian);
}

void	mlx_run(int **bitmap)
{
	t_ray_tracer_data	*rt_data;

	rt_data = NULL;
	init_mlx(&rt_data);
	render_image(rt_data, bitmap);
	mlx_key_hook(rt_data->mlx_data->window_ptr, handle_key_input, rt_data);
	mlx_hook(rt_data->mlx_data->window_ptr, 17, 0, close_window, rt_data);
	free_bitmap(bitmap);
	mlx_loop(rt_data->mlx_data->mlx_ptr);
}
