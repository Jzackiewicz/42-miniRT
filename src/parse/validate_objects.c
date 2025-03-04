/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:16:47 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 12:59:40 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void    validate_sphere(char **line_split, char *line)
{
    if (!line || !line_split)
        clean_on_error(line_split);
    if (ft_2d_strlen(line_split) != 4)
        clean_on_error(line_split);
    if (check_cords(line_split[1]) == -1)
        clean_on_error(line_split);
    if (!is_valid_float(line_split[2]))
        clean_on_error(line_split);
    if (check_colors(line_split[3]) == -1)
        clean_on_error(line_split);
}

void    validate_plane(char **line_split, char *line)
{
    if (!line || !line_split)
		clean_on_error(line_split);
	if (ft_2d_strlen(line_split) != 4)
		clean_on_error(line_split);
    if (check_cords(line_split[1]) == -1)
        clean_on_error(line_split);
    if (check_vector(line_split[2]) == -1)
        clean_on_error(line_split);
    if (check_colors(line_split[3]) == -1)
        clean_on_error(line_split);
}

void    validate_cylinder(char **line_split, char *line)
{
    if (!line || !line_split)
        clean_on_error(line_split);
    if (ft_2d_strlen(line_split) != 6)
        clean_on_error(line_split);
    if (check_cords(line_split[1]) == -1)
        clean_on_error(line_split);
    if (check_vector(line_split[2]) == -1)
        clean_on_error(line_split);
    if (!is_valid_float(line_split[3]))
        clean_on_error(line_split);
    if (!is_valid_float(line_split[4]))
        clean_on_error(line_split);
    if (check_colors(line_split[5]) == -1)
        clean_on_error(line_split);
}