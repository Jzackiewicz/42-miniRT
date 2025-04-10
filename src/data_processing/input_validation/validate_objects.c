/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:16:47 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/04 17:29:49 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

static int	validate_sphere(char **line_split)
{
	if (!line_split)
		return (clean_on_error(line_split));
	if (ft_2d_strlen(line_split) != 4)
		return (clean_on_error(line_split));
	if (check_coords(line_split[1]) == -1)
		return (clean_on_error(line_split));
	if (!is_valid_float(line_split[2]) || ft_atof(line_split[2]) < 0.0)
		return (clean_on_error(line_split));
	if (check_colors(line_split[3]) == -1)
		return (clean_on_error(line_split));
	return (0);
}

static int	validate_plane(char **line_split)
{
	if (!line_split)
		return (clean_on_error(line_split));
	if (ft_2d_strlen(line_split) != 4)
		return (clean_on_error(line_split));
	if (check_coords(line_split[1]) == -1)
		return (clean_on_error(line_split));
	if (check_vector(line_split[2], -1) == -1)
		return (clean_on_error(line_split));
	if (check_colors(line_split[3]) == -1)
		return (clean_on_error(line_split));
	return (0);
}

static int	validate_cylinder(char **line_split)
{
	if (!line_split)
		return (clean_on_error(line_split));
	if (ft_2d_strlen(line_split) != 6)
		return (clean_on_error(line_split));
	if (check_coords(line_split[1]) == -1)
		return (clean_on_error(line_split));
	if (check_vector(line_split[2], -1) == -1)
		return (clean_on_error(line_split));
	if (!is_valid_float(line_split[3]) || ft_atof(line_split[3]) < 0.0)
		return (clean_on_error(line_split));
	if (!is_valid_float(line_split[4]))
		return (clean_on_error(line_split));
	if (check_colors(line_split[5]) == -1)
		return (clean_on_error(line_split));
	return (0);
}

// returns 0 on successful validation
// 1 on id not found
// -1 on unsuccessful validation
int	validate_objects(char **line_split, int fd, t_key_presence *key_presence)
{
	if (!ft_strncmp(line_split[0], "sp\0", 3))
	{
		if (validate_sphere(line_split) == -1)
			return (drain_file(fd));
		key_presence->no_present[SPHERE]++;
		return (0);
	}
	else if (!ft_strncmp(line_split[0], "pl\0", 3))
	{
		if (validate_plane(line_split) == -1)
			return (drain_file(fd));
		key_presence->no_present[PLANE]++;
		return (0);
	}
	else if (!ft_strncmp(line_split[0], "cy\0", 3))
	{
		if (validate_cylinder(line_split) == -1)
			return (drain_file(fd));
		key_presence->no_present[CYLINDER]++;
		return (0);
	}
	else
		return (1);
}
