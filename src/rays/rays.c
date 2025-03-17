/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:32:48 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/17 09:18:03 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

t_ray	*create_ray(double *origin, double *direction)
{
	t_ray	*new_ray;

	new_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!new_ray)
		return (NULL);
	new_ray->origin = origin;
	new_ray->direction = direction;
	new_ray->t = 0;
	return (new_ray);
}

double	*position(t_ray *ray, double t)
{
	double	*dir_t;
	double	*pos;

	dir_t = multiply_tuple(ray->direction, t);
	pos = add_tuple(ray->origin, dir_t);
	free(dir_t);
	return (pos);
}

static t_input_data	*find_camera(t_input_data **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!ft_strncmp(data[i]->id, "C\0", 2))
			return (data[i]);
		i++;
	}
	return (NULL);
}
/* viewport, a "screen" through which the rays will pass */
void	cam_shot(t_ray **rays, t_input_data **data)
{
	t_input_data *camera;
	double viewport_h;
	double viewport_w;
	double aspect_ratio;

	(void)rays;
	camera = find_camera(data);
	if (!camera)
		return ;
	// degrees to radians
	viewport_h = 2.0 * tan((camera->fov * M_PI / 180.0) / 2.0);
	aspect_ratio = (double) WINDOW_WIDTH / (double) WINDOW_HEIGHT;
	viewport_w = viewport_h * aspect_ratio;

	// an orthogonal coordinate system, not cartesian obv
	// w back of the camera, u- up, v- right the last two are perpendicular
	// maybeeeeeeeeee
	// double w[4], u[4], v[4];
	// vec_normalize (direction, w);
	// vec_scale(w, -1.0, w);
}
