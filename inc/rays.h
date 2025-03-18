/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:34:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/03/18 10:21:28 by jzackiew         ###   ########.fr       */
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

typedef struct s_object	t_object;
typedef struct s_camera	t_camera;

t_ray					*create_ray(double *origin, double *direction);
double					*position(t_ray *ray, double t);
// double			*init_cylinder_quad(t_input_data *obj, t_ray *ray,
// 					double *oc_vector);
// void			free_cylinder_resources(double *arr_t, double *oc_vector,
// 					double *quad);
// double			*init_result_t(void);
// double			*init_cylinder_quad(t_input_data *obj, t_ray *ray,
// 					double *oc_vector);
// double			check_height_constraints(t_input_data *obj, t_ray *ray,
// 					double *oc_vector, double t);
// int				check_cylinder_discriminant(double *quad, double **arr_t,
// 					double *oc_vector);
// double			*calculate_intersection_points(t_input_data *obj,
// t_ray *ray,
// 					double *oc_vector, double *quad);
// void			find_closest_t(double *side_t, double *caps_t, double *t1,
// 					double *t2);
// double			*intersect_cylinder(t_input_data *obj, t_ray *ray);
// void			clean_intersect_memory(double *side_t, double *caps_t);
// void			free_cylinder_resources(double *arr_t, double *oc_vector,
// 					double *quad);

double					*intersect(t_object *obj, t_ray *ray);
void					sort_intersections(t_intersec **i_s, int start_index,
							int end_index);
t_intersec				**get_sorted_intersections(t_ray *ray, t_object **objs);
t_intersec				*identify_hit(t_intersec **i_s);
t_ray					**generate_rays(t_camera *cam_data);
int					**generate_bitmap(t_intersec ***ray_intersections, t_ray **rays, t_camera *cam_data);
double	get_canvas_width(t_camera *cam_data);
int						count_intersections(t_intersec **intersex);
t_intersec				***find_all_intersections(t_ray **rays,
							t_object **objs);

#endif