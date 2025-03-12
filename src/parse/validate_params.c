/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:02:01 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/05 17:28:01 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	is_valid_color(char **colors_split)
{
	int	i;
	int	value;

	i = -1;
	while (++i < 3)
	{
		if (!is_valid_number(colors_split[i])
			|| check_for_overflow(colors_split[i]))
			return (-1);
		value = ft_atoi(colors_split[i]);
		if (value < 0 || value > 255)
			return (-1);
	}
	return (0);
}

int	check_colors(char *colors)
{
	char	**colors_split;

	if (!colors || colors[ft_strlen(colors) - 1] == ',')
		return (-1);
	colors_split = ft_split(colors, ',');
	if (!colors_split || ft_2d_strlen(colors_split) != 3)
		return (ft_arr2d_free(colors_split), -1);
	if (is_valid_color(colors_split) == -1)
		return (ft_arr2d_free(colors_split), -1);
	return (ft_arr2d_free(colors_split), 0);
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

static void	cnv_xyz(char **vector_split, double *x, double *y, double *z)
{
	*x = ft_atof(vector_split[0]);
	*y = ft_atof(vector_split[1]);
	*z = ft_atof(vector_split[2]);
}

// i passed with -1
int	check_vector(char *vector, int i)
{
	char	**vector_split;
	double	x;
	double	y;
	double	z;
	double	magnitude;

	if (!vector || vector[ft_strlen(vector) - 1] == ',')
		return (-1);
	vector_split = ft_split(vector, ',');
	if (!vector_split || ft_2d_strlen(vector_split) != 3)
		return (ft_arr2d_free(vector_split), -1);
	while (++i < 3)
	{
		if (!is_valid_float(vector_split[i]))
			return (ft_arr2d_free(vector_split), -1);
	}
	cnv_xyz(vector_split, &x, &y, &z);
	if (x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0 || z < -1.0 || z > 1.0)
		return (ft_arr2d_free(vector_split), -1);
	magnitude = sqrt(x * x + y * y + z * z);
	if (fabs(magnitude - 1.0) > 0.0001)
		return (ft_arr2d_free(vector_split), -1);
	return (ft_arr2d_free(vector_split), 0);
}
