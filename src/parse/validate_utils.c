/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:19:50 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/04 12:58:21 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	clean_on_error(char **line_split)
{
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

