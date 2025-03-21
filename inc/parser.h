/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:21:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/21 12:56:19 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// SECTION: includes
# include "../lib/libft/libft.h"
# include <math.h>

// SECTION: key validation
// array indexes of each id type for presence checks
# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2
# define SPHERE 3
# define PLANE 4
# define CYLINDER 5

typedef struct s_key_presence
{
	int				no_present[6];
}					t_key_presence;

// SECTION: data structures for objects and settings
typedef struct s_input_data
{
	char			*id;
	// ambient specific
	double			ambient_light_ratio;
	// camera specific
	double			*orientation_vector;
	int				fov;
	// light specific
	double			brightness;
	// sphere/cylinder specific
	double			diameter;
	double			height;
	// common
	int				*color;
	double			*coords;
	double			*vector;
}					t_input_data;

// SECTION: validation functions
int					check_colors(char *color);
int					check_coords(char *coords);
int					check_vector(char *vector, int i);
int					is_valid_number(const char *str);
int					is_valid_float(const char *str);
int					drain_file(int fd);
int					validate_settings(char **line_split, int fd,
						t_key_presence *key_presence);
int					validate_objects(char **line_split, int fd,
						t_key_presence *key_presence);
int					clean_on_error(char **line_split);
int					validate_file(char *filepath);

// SECTION: parsing functions
void				init_with_default(t_input_data *obj);
void				parse_colors(char *color, t_input_data *obj);
void				parse_vector(char *vector, t_input_data *obj);
void				parse_coords(char *coords, t_input_data *obj);
void				parse_settings(char **line_split, t_input_data **objects,
						int i);
void				parse_objects(char **line_split, t_input_data **objects,
						int i);

int					parse_file(char *filepath, t_input_data ***objects);

typedef struct s_ambient t_ambient;
typedef struct s_object t_object;

struct s_object		**get_objects(t_input_data **data, int no_data);
struct s_camera		*get_cam_data(t_input_data **data, int no_data);
struct s_light		*get_light_data(t_input_data **data, int no_data);
void				assign_object_material(t_ambient *ambient, t_object *obj);
struct s_ambient	*get_ambient_data(t_input_data **data, int no_data);
int					count_objects(struct s_object **objs);

// debug utils
void				print_object(t_input_data *obj);

#endif