/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:46:52 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:06 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/graphics.h"

void	free_window(t_mlx_data *mlx_data)
{
	if (mlx_data->window_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->window_ptr);
	if (mlx_data)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

void	free_image(t_mlx_data *mlx_data)
{
	if (mlx_data->img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
		free(mlx_data->img_addr);
		free(mlx_data->img_ptr);
	}
}

void	clean_mlx(t_ray_tracer_data *rt_data)
{
	free_window(rt_data->mlx_data);
	free_image(rt_data->mlx_data);
	free(rt_data->mlx_data);
	free(rt_data);
}

int	close_window(t_ray_tracer_data *rt_data, int errno)
{
	clean_mlx(rt_data);
	exit(errno);
	return (0);
}

int	handle_key_input(int keysym, t_ray_tracer_data *rt_data)
{
	if (keysym == XK_Escape)
		close_window(rt_data, 1);
	return (0);
}
