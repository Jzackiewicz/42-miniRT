/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:13:36 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/22 16:21:25 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

static int	validate_ambient(char **line_split)
{
	if (!line_split)
		return (clean_on_error(line_split));
	if (ft_2d_strlen(line_split) != 3)
		return (clean_on_error(line_split));
	if (!is_valid_float(line_split[1], -1, 0, 0) || ft_atof(line_split[1]) < 0.0
		|| ft_atof(line_split[1]) > 1.0)
		return (clean_on_error(line_split));
	if (check_colors(line_split[2]) == -1)
		return (clean_on_error(line_split));
	return (0);
}

static int	validate_camera(char **line_split)
{
	int	fov;

	if (!line_split)
		return (clean_on_error(line_split));
	if (ft_2d_strlen(line_split) != 4)
		return (clean_on_error(line_split));
	if (check_coords(line_split[1]) == -1)
		return (clean_on_error(line_split));
	if (check_vector(line_split[2], -1) == -1)
		return (clean_on_error(line_split));
	if (!is_valid_number(line_split[3]) || check_for_overflow(line_split[3]))
		return (clean_on_error(line_split));
	fov = ft_atoi(line_split[3]);
	if (fov < 0 || fov > 180)
		return (clean_on_error(line_split));
	return (0);
}

static int	validate_light(char **line_split)
{
	if (!line_split)
		return (clean_on_error(line_split));
	if (ft_2d_strlen(line_split) != 4)
		return (clean_on_error(line_split));
	if (check_coords(line_split[1]) == -1)
		return (clean_on_error(line_split));
	if (!is_valid_float(line_split[2], -1, 0, 0) || ft_atof(line_split[2]) > 1.0
		|| ft_atof(line_split[2]) < 0.0)
		return (clean_on_error(line_split));
	if (check_colors(line_split[3]) == -1)
		return (clean_on_error(line_split));
	return (0);
}

// returns 0 on successful validation
// 1 on id not found
// -1 on unsuccessful validation
int	validate_settings(char **line_split, int fd, t_key_presence *key_presence)
{
	if (!ft_strncmp(line_split[0], "A\0", 2))
	{
		if (validate_ambient(line_split) == -1)
			return (drain_file(fd));
		key_presence->no_present[AMBIENT]++;
		return (0);
	}
	else if (!ft_strncmp(line_split[0], "C\0", 2))
	{
		if (validate_camera(line_split) == -1)
			return (drain_file(fd));
		key_presence->no_present[CAMERA]++;
		return (0);
	}
	else if (!ft_strncmp(line_split[0], "L\0", 2))
	{
		if (validate_light(line_split) == -1)
			return (drain_file(fd));
		return (0);
	}
	else
		return (1);
}
