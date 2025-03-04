/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:21:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 15:20:52 by agarbacz         ###   ########.fr       */
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
int     drain_file(int fd);
int	    validate_settings(char **line_split, int fd);
int     validate_objects(char **line_split, int fd);
int     clean_on_error(char **line_split);
int     validate_file(char *filepath);

#endif