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

void clean_mlx(t_ray_tracer_data *rt_data)
{
    if (!rt_data)
        return;
    if (rt_data->mlx_data)
    {
        if (rt_data->mlx_data->img_ptr && rt_data->mlx_data->mlx_ptr)
            mlx_destroy_image(rt_data->mlx_data->mlx_ptr, rt_data->mlx_data->img_ptr);
        
        if (rt_data->mlx_data->window_ptr && rt_data->mlx_data->mlx_ptr)
            mlx_destroy_window(rt_data->mlx_data->mlx_ptr, rt_data->mlx_data->window_ptr);
        
        if (rt_data->mlx_data->mlx_ptr)
            mlx_destroy_display(rt_data->mlx_data->mlx_ptr);
            
        free(rt_data->mlx_data->mlx_ptr);
        free(rt_data->mlx_data);
    }
    free(rt_data);
}

int	close_window(t_ray_tracer_data *rt_data, int errno)
{
	clean_mlx(rt_data);
	errno = 0;
	exit(errno);
	return (0);
}