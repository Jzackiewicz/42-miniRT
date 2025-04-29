/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:58:11 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/29 17:07:30 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 10e-6

# include "../lib/libft/libft.h"
# include "data_processing.h"
# include "graphics.h"
# include "operations.h"
# include "rays.h"
# include "scene.h"
# include <math.h>
# include <stdbool.h>

typedef struct s_comps
{
	double			t;
	t_object		*obj;
	double			*point;
	double			*over_point;
	double			*eyev;
	double			*normalv;
}					t_comps;

typedef struct s_object
{
	char			*id;
	double			diameter;
	double			height;
	double			*color;
	double			*coords;
	double			*orientation_vector;
	struct s_matrix	*transform;
	struct s_matrix	*inv_transform;
	bool			is_checkered;
	char			*texture_path;
	t_texture		*texture;
}					t_object;

typedef struct s_camera
{
	double			*origin;
	double			*orientation_vector;
	double			fov;
	struct s_matrix	*transform;
	struct s_matrix	*inv_transform;
	double			half_width;
	double			half_height;
	double			pixel_size;
}					t_camera;

typedef struct s_light
{
	double			*coords;
	double			brightness;
	double			*color;
}					t_light;

typedef struct s_ambient
{
	double			brightness;
	double			*color;
}					t_ambient;

#endif