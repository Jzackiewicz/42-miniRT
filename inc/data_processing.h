/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:21:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/22 15:36:43 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_PROCESSING_H
# define DATA_PROCESSING_H

// SECTION: includes
# include "../lib/libft/libft.h"
# include <math.h>
# include <stdbool.h>

// SECTION: key validation
// array indexes of each id type for presence checks
# define AMBIENT 0
# define CAMERA 1
# define SPHERE 2
# define PLANE 3
# define CYLINDER 4
# define CONE 5

typedef struct s_key_presence
{
	int						no_present[6];
}							t_key_presence;

typedef struct s_input_data
{
	char					*id;
	// ambient specific
	double					ambient_light_ratio;
	// camera specific
	double					*orientation_vector;
	int						fov;
	// light specific
	double					brightness;
	// sphere/cylinder specific
	double					diameter;
	double					height;
	// common
	int						*color;
	double					*coords;
	double					*vector;
	bool					is_checkered;
	const char				*texture_path;
}							t_input_data;

// 							Input_validation
int							check_colors(char *color);
int							check_coords(char *coords);
int							check_vector(char *vector, int i);
int							is_valid_number(const char *str);
int							is_valid_float(const char *str);
int							validate_texture_file(const char *path);
int							drain_file(int fd);
int							validate_settings(char **line_split, int fd,
								t_key_presence *key_presence);
int							validate_objects(char **line_split, int fd,
								t_key_presence *key_presence);
int							clean_on_error(char **line_split);
int							validate_file(char *filepath);

//							Parsing
void						init_with_default(t_input_data *obj);
void						parse_colors(char *color, t_input_data *obj);
void						parse_vector(char *vector, t_input_data *obj);
void						parse_coords(char *coords, t_input_data *obj);
void						parse_settings(char **line_split,
								t_input_data **objects, int i);
void						parse_objects(char **line_split,
								t_input_data **objects, int i);

int							parse_file(char *filepath, t_input_data ***objects);

typedef struct s_ambient	t_ambient;
typedef struct s_object		t_object;
typedef struct s_camera		t_camera;
typedef struct s_world		t_world;

struct s_object				**get_objects(t_input_data **data);
struct s_camera				*get_cam_data(t_input_data **data);
void						assign_pixel_size(struct s_camera *cam_data);
struct s_light				**get_light_data(t_input_data **data);
struct s_ambient			*get_ambient_data(t_input_data **data);
int							count_objects(struct s_object **objs);

//							Partition
int							get_no_obj_elems(t_input_data **data);
int							get_no_light_elems(t_input_data **data);
t_object					*assign_object(t_input_data *data);
void						load_camera_transform_matrix(t_camera *cam_data);

typedef struct s_ray_tracer_data t_ray_tracer_data;

// 							Debug
void						print_object(t_input_data *obj);
void						free_world(t_world *world, t_ray_tracer_data *rt_data);
void						free_input_data(t_input_data **inp_data,
								int no_lines);

//							Utils
double						*convert_color(int *int_color);

#endif