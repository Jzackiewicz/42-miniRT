/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:13:36 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/03 16:20:24 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void    validate_ambient(char **line_split, char *line)
{
    if (ft_2d_strlen != 3)
        clean_on_error(line_split, line);
    if (ft_atof(line_split[1]) < 0.0 || ft_atof(line_split[1]) > 1.0)
        clean_on_error(line_split, line);
    if (check_colors(line_split[2]) == -1)
        clean_on_error(line_split, line);
}

void    validate_camera(char **line_split, char *line);

void    validate_light(char **line_split, char *line);