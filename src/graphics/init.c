/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:15:56 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/13 16:30:26 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/graphics.h"

void	init_mlx(t_ray_tracer_data **rt_data)
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
			&(*rt_data)->bits_per_pixel, &(*rt_data)->line_length,
			&(*rt_data)->endian);
}
