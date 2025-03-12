/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_overflow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:10:07 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/03 16:52:55 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_for_overflow(char *nbr)
{
	char	*str_int_limit;
	int		int_limit_strlen;
	int		nbr_strlen;

	int_limit_strlen = 10;
	nbr_strlen = ft_strlen(nbr);
	if (nbr[0] == '-')
		int_limit_strlen++;
	if (nbr_strlen > int_limit_strlen)
		return (1);
	else if (nbr_strlen == int_limit_strlen)
	{
		if (nbr[0] == '-')
			str_int_limit = ft_itoa(INT_MIN);
		else
			str_int_limit = ft_itoa(INT_MAX);
		if (ft_strncmp(nbr, str_int_limit, int_limit_strlen) > 0)
			return (free(str_int_limit), 1);
		free(str_int_limit);
	}
	return (0);
}
