/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:21:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/10 19:34:53 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// SECTION: includes
# include "../lib/libft/libft.h"
# include "miniRT.h"

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
	int		no_present[6];
}			t_key_presence;

// SECTION: data structures for objects and settings
typedef struct s_object
{
	char	*id;
	// ambient specific
	double	ambient_light_ratio;
	// camera specific
	double	*orientation_vector;
	int		fov;
	// light specific
	double	brightness;
	// sphere/cylinder specific
	double	diameter;
	double	height;
	// common
	int		*colors;
	double	*cords;
	double	*vector;
}			t_object;

// each struct for each object, store all in one

// SECTION: validation functions
int			check_colors(char *colors);
int			check_cords(char *cords);
int			check_vector(char *vector, int i);
int			is_valid_number(const char *str);
int			is_valid_float(const char *str);
int			drain_file(int fd);
int			validate_settings(char **line_split, int fd,
				t_key_presence *key_presence);
int			validate_objects(char **line_split, int fd,
				t_key_presence *key_presence);
int			clean_on_error(char **line_split);
int			validate_file(char *filepath);

// SECTION: parsing functions
void		init_with_default(t_object *obj);
void		parse_colors(char *colors, t_object *obj);
void		parse_vector(char *vector, t_object *obj);
void		parse_cords(char *cords, t_object *obj);

void		parse_settings(char **line_split, t_object **objects, int i);

void		free_object(t_object *obj);

void		parse_file(char *filepath);

// debug utils
void		print_object(t_object *obj);

#endif