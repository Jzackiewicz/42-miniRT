/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:13:36 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/03 14:20:04 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void    validate_ambient(char **line_split, char *line)
{
    if (ft_2d_strlen != 3)
    {
        free(line);
        ft_arr2d_free(line_split);
        exit(1);
    }
    
}

void    validate_camera(char **line_split, char *line);

void    validate_light(char **line_split, char *line);