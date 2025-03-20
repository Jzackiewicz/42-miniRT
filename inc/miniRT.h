/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:58:11 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/20 14:59:00 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "graphics.h"
# include "operations.h"
# include "parser.h"
# include "rays.h"
# include <math.h>

typedef struct s_object
{
	char			*id;
	double			diameter;
	double			height;
	int				*color;
	double			*coords;
	double			*orientation_vector;
	struct s_matrix	*transform;
	t_material		*material;
}					t_object;

typedef struct s_material
{
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;

}					t_material;

typedef struct s_camera
{
	double			*origin;
	double			*orientation_vector;
	int				fov;
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

void				clean_intersections(t_intersec ***ray_intersex);
void				clean_rays(t_ray **rays);
void				free_objects(t_input_data **inp_data, t_object **objs,
						int no_lines);
void				free_bitmap(int **bitmap);
void				clean_objects(t_object **objs, t_input_data **data,
						int no_lines);

#endif