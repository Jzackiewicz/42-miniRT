/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:46:52 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/03 09:10:03 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/window.h"

void	free_window(t_mlx_data *mlx_data)
{
	if (mlx_data->win_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

int	close_window(t_mlx_data *mlx_data, int errno)
{
	free_window(mlx_data);
	exit(errno);
	return (0);
}

int	handle_key_input(int keysym, t_mlx_data *mlx_data)
{
	if (keysym == XK_Escape)
		close_window(mlx_data, 1);
	return (0);
}

void	prepare_window(void)
{
	t_mlx_data	mlx_data;

	mlx_data.mlx_ptr = mlx_init();
	if (!mlx_data.mlx_ptr)
		close_window(&mlx_data, -1);
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "miniRT");
	if (!mlx_data.mlx_ptr)
		close_window(&mlx_data, -1);
	mlx_key_hook(mlx_data.win_ptr, handle_key_input, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 17, 0, close_window, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}
