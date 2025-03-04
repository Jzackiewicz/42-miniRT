/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:19:50 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 10:53:42 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	clean_on_error(char **line_split, char *line)
{
	if (line)
		free(line);
	if (line_split)
		ft_arr2d_free(line_split);
	exit(1);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int is_valid_float(const char *str)
{
    int i = 0;
    int has_dot = 0;
    int has_digit = 0;

    if (!str || !*str)  
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] == '.')
        {
            if (has_dot)
                return (0);
            has_dot = 1;
        }
        else if (!ft_isdigit(str[i]))
            return (0);
        else
            has_digit = 1;
        i++;
    }
    return (has_digit);
}

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
	i = 0;
	while (i < 3)
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
		i++;
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
