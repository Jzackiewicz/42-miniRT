/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:02 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/23 13:39:09 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_nbr_len(unsigned int nbr)
{
	int	str_len;

	str_len = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		str_len++;
	}
	return (str_len);
}

char	*ft_utoa(unsigned int nbr)
{
	char			*new_string;
	int				str_len;

	str_len = get_nbr_len(nbr);
	new_string = (char *)malloc((str_len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	new_string[str_len] = 0;
	while (str_len)
	{
		str_len--;
		new_string[str_len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (new_string);
}
