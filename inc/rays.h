/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/04/17 17:30:21 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "../lib/libft/libft.h"
# include "data_processing.h"
# include "graphics.h"
# include "operations.h"
# include <stdbool.h>

# define SPHERE_CHECKER_SCALE 3.0
# define PLANE_CHECKER_SCALE 0.5
# define CYLINDER_CHECKER_SCALE 1.0 // tmp

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

typedef struct s_checker_pattern
{
	int					color_a;
	int					color_b;
	t_matrix			*transform;
	t_matrix			*inv_transform;
}						t_checker_p;

typedef struct s_light	t_light;
typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

t_ray					*create_ray(double *origin, double *direction);
void					free_ray(t_ray *ray);
double					*position(t_ray *ray, double t);
double					*intersect_cylinder(t_ray *ray, t_object *obj);
double					*intersect(t_object *obj, t_ray *ray);
t_intersec				**get_intersections(t_ray *ray, t_object **objs);
void					sort_intersections(t_intersec **i_s, int start_index,
							int end_index);
t_intersec				**get_sorted_intersections(t_ray *ray, t_object **objs);
t_intersec				*identify_hit(t_intersec **i_s);
void					free_intersections(t_intersec **ray_intersex);

// light section
typedef struct s_comps	t_comps;
typedef struct s_light	t_light;

double					*get_checkered_color(t_object *obj, double *point);
bool					is_shadowed(t_world *w, double *p, int light_index);
double					*apply_phong_attributes(t_world *world, t_comps *comps,
							double *new_color);
int						get_pixel_color(t_world *world, t_comps *comps);
#endif