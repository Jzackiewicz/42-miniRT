/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:19:50 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/03 17:05:40 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	clean_on_error(char **line_split, char *line)
{
	free(line);
	ft_arr2d_free(line_split);
	exit(1);
}

static int	is_valid_number(const char *str)
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
