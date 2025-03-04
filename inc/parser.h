/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:21:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 12:59:13 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lib/libft/libft.h"
# include "miniRT.h"

int		check_extension(char *filepath);
int		check_colors(char *colors);
int		check_cords(char *cords);
int		check_vector(char *vector);
int		is_valid_number(const char *str);
int		is_valid_float(const char *str);
void	validate_ambient(char **line_split, char *line);
void	validate_camera(char **line_split, char *line);
void	validate_light(char **line_split, char *line);
void    validate_cylinder(char **line_split, char *line);
void    validate_plane(char **line_split, char *line);
void    validate_sphere(char **line_split, char *line);
void	clean_on_error(char **line_split);
void	validate_file(char *filepath);

#endif