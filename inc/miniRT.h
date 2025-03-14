/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:58:11 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/14 13:41:08 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "operations.h"
# include "parser.h"
# include "rays.h"
# include "graphics.h"
# include <math.h>

typedef	struct	s_object
{
	char	*id;
	double	diameter;
	double	height;
	int		*color;
	double	*coords;
	double	*normal_vector;
}				t_object;

typedef struct	s_camera
{
	double	*origin;
	double	*normal_vector;
	int		fov;
}				t_camera;

typedef struct	s_light
{
	double	*origin;
	double	brightness;
	int		*color;
}				t_light;

typedef struct	s_ambient
{
	double	brightness;
	int		*color;
}				t_ambient;

void	clean_rays(t_intersec **ray_intersex, t_ray *ray);
void	clean_objects(t_object **objs, t_input_data **data, int no_lines);

#endif