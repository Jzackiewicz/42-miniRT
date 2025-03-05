/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:21:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/05 19:03:34 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lib/libft/libft.h"
# include "miniRT.h"

// array indexes of each id type for presence checks
# define AMBIENT 0
# define CAMERA 1
# define LIGHT 2
# define SPHERE 3
# define PLANE 4
# define CYLINDER 5

typedef struct s_key_presence
{
	int	no_present[6];
}		t_key_presence;

int		check_colors(char *colors);
int		check_cords(char *cords);
int		check_vector(char *vector, int i);
int		is_valid_number(const char *str);
int		is_valid_float(const char *str);
int		drain_file(int fd);
int		validate_settings(char **line_split, int fd,
			t_key_presence *key_presence);
int		validate_objects(char **line_split, int fd,
			t_key_presence *key_presence);
int		clean_on_error(char **line_split);
int		validate_file(char *filepath);

#endif