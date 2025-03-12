/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:09:10 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/03 16:09:28 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = get_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str - '0') * fraction;
			fraction *= 0.1;
			str++;
		}
	}
	return (result * sign);
}
