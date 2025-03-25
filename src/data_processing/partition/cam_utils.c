#include "../../../inc/miniRT.h"

/* calculates the pixel_size and assigns inside of the t_camera structure.
*  assigns also the attributes: half_width & half_height */
void	assign_pixel_size(t_camera *cam_data)
{
	double half_view;
	double aspect;

	half_view = tan(cam_data->fov / 2);
	aspect = WINDOW_HEIGHT / WINDOW_WIDTH;
	if (aspect >= 1)
	{
		cam_data->half_width = half_view;
		cam_data->half_height = half_view / aspect;
	}
	else
	{
		cam_data->half_width = half_view * aspect;
		cam_data->half_height = half_view;
	}
	cam_data->pixel_size = (cam_data->half_width * 2) / WINDOW_HEIGHT;
}

