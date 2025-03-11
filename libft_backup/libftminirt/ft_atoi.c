/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:13:52 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 11:41:12 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	output;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	output = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		if (nptr[i + 1] == '-' || nptr[i + 1] == '+')
			return (sign * output);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output = 10 * output + (nptr[i] - '0');
		i++;
	}
	return (sign * output);
}

/* int main()
{
	printf("%d", ft_atoi(" 			\f	-897s4"));
} */