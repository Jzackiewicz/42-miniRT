/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:02:01 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 12:05:30 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// returns -1 on error
int	check_colors(char *colors)
{
	char	**colors_split;
	int		i;
	int		value;

	if (!colors || colors[ft_strlen(colors) - 1] == ',')
		return (-1);
	colors_split = ft_split(colors, ',');
	if (!colors_split)
		return (-1);
	if (ft_2d_strlen(colors_split) != 3)
	{
		ft_arr2d_free(colors_split);
		return (-1);
	}
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_number(colors_split[i])
			|| check_for_overflow(colors_split[i]))
		{
			ft_arr2d_free(colors_split);
			return (-1);
		}
		value = ft_atoi(colors_split[i]);
		if (value < 0 || value > 255)
		{
			ft_arr2d_free(colors_split);
			return (-1);
		}
	}
	ft_arr2d_free(colors_split);
	return (0);
}

int	check_cords(char *cords)
{
	char	**cords_split;
	int		i;

	if (!cords || cords[ft_strlen(cords) - 1] == ',')
		return (-1);
	cords_split = ft_split(cords, ',');
	if (!cords_split)
		return (-1);
	if (ft_2d_strlen(cords_split) != 3)
	{
		ft_arr2d_free(cords_split);
		return (-1);
	}
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_float(cords_split[i]))
		{
			ft_arr2d_free(cords_split);
			return (-1);
		}
	}
	ft_arr2d_free(cords_split);
	return (0);
}

int	check_vector(char *vector)
{
	char	**vector_split;
	int		i;
	double	x, y, z, magnitude;

	if (!vector || vector[ft_strlen(vector) - 1] == ',')
		return (-1);
	vector_split = ft_split(vector, ',');
	if (!vector_split)
		return (-1);
	if (ft_2d_strlen(vector_split) != 3)
	{
		ft_arr2d_free(vector_split);
		return (-1);
	}
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_float(vector_split[i]))
		{
			ft_arr2d_free(vector_split);
			return (-1);
		}
	}
	x = ft_atof(vector_split[0]);
	y = ft_atof(vector_split[1]);
	z = ft_atof(vector_split[2]);
	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0)
	{
		ft_arr2d_free(vector_split);
		return (-1);
	}
	magnitude = sqrt(x * x + y * y + z * z);
	if (fabs(magnitude - 1.0) > 0.0001)
	{
		ft_arr2d_free(vector_split);
		return (-1);
	}
	ft_arr2d_free(vector_split);
	return (0);
}
