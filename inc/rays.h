/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/24 18:22:59 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "../lib/libft/libft.h"
# include "graphics.h"
# include "operations.h"
# include "parser.h"

typedef struct s_ray // xD
{
	double *origin;
	double *direction;
}						t_ray;

typedef struct s_intersec
{
	double				t;
	struct s_object		*object;
}						t_intersec;

typedef struct s_light t_light;
typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

t_ray					*create_ray(double *origin, double *direction);
t_ray					**generate_rays(t_camera *cam_data);
double					*position(t_ray *ray, double t);
double					*intersect(t_object *obj, t_ray *ray);
void					sort_intersections(t_intersec **i_s, int start_index,
							int end_index);
t_intersec				**get_sorted_intersections(t_ray *ray, t_object **objs);
t_intersec				*identify_hit(t_intersec **i_s);
t_intersec				***intersect_world(t_ray **rays,
							t_object **objs);
int						count_intersections(t_intersec **intersex);
int						**generate_bitmap(t_intersec ***ray_intersections,
							t_ray **rays, t_camera *cam_data, t_light *light);


//				spacial_conversion
void					load_transform_matrix(t_object *obj);
t_ray					*ray_to_object_space(t_ray *ray, t_object *obj);
int						rgb_to_int(double r, double g, double b);

typedef struct s_light	t_light;

// light section
double					*get_normal_at(t_object *obj, double *w_point);
double					*reflect(double *in, double *normal);
double					lighting(t_light *light, t_object *obj,
							t_camera *cam_data, double *normal, double *point);

#endif