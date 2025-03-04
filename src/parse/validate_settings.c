/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:13:36 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 11:09:27 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	validate_ambient(char **line_split, char *line)
{
	if (!line || !line_split)
		clean_on_error(line_split, line);
	if (ft_2d_strlen(line_split) != 3)
		clean_on_error(line_split, line);
	if (!is_valid_float(line_split[1]) || ft_atof(line_split[1]) < 0.0
		|| ft_atof(line_split[1]) > 1.0)
		clean_on_error(line_split, line);
	if (check_colors(line_split[2]) == -1)
		clean_on_error(line_split, line);
	return (0);
}

int	validate_camera(char **line_split, char *line)
{
	int	fov;

	if (!line || !line_split)
		return (-1);
	if (ft_2d_strlen(line_split) != 4)
		return (-1);
	if (check_cords(line_split[1]) == -1)
		return (-1);
	if (check_vector(line_split[2]) == -1)
		return (-1);
	if (!is_valid_number(line_split[3]) || check_for_overflow(line_split[3]))
		return (-1);
	fov = ft_atoi(line_split[3]);
	if (fov < 0 || fov > 180)
		return (-1);
	return (0);
}

void	validate_light(char **line_split, char *line);