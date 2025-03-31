/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:43 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/31 10:13:56 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/graphics.h"

static void	free_window(t_mlx_data *mlx_data)
{
	if (mlx_data->window_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->window_ptr);
	if (mlx_data)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

static void	free_image(t_mlx_data *mlx_data)
{
	if (mlx_data->img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
		free(mlx_data->img_addr);
		free(mlx_data->img_ptr);
	}
}

static void	clean_mlx(t_ray_tracer_data *rt_data)
{
	if (!rt_data)
		return ;
	if (rt_data->mlx_data)
	{
		free_image(rt_data->mlx_data);
		free_window(rt_data->mlx_data);
		free(rt_data->mlx_data);
	}
	free(rt_data);
}

int	close_window(t_ray_tracer_data *rt_data, int errno)
{
	clean_mlx(rt_data);
	exit(errno);
	return (0);
}
