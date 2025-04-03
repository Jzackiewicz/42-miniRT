/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:58:11 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/03 10:17:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "graphics.h"
# include "operations.h"
# include "data_processing.h"
# include "rays.h"
# include "scene.h"
# include <math.h>
# include <stdbool.h>

typedef struct s_comps
{
	double			t;
	t_object		*obj;
	double			*point;
	double			*eyev;
	double			*normalv;
	bool			inside;
}					t_comps;

typedef struct s_object
{
	char			*id;
	double			diameter;
	double			height;
	int				*color;
	double			*coords;
	double			*orientation_vector;
	struct s_matrix	*transform;
	struct s_matrix	*inv_transform;
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
	int				*color;
}					t_light;

typedef struct s_ambient
{
	double			brightness;
	int				*color;
}					t_ambient;

#endif