/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:35:13 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/18 08:27:45 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_convnum_len(uintptr_t nbr, char *base)
{
	int	len;

	len = 0;
	while (nbr)
	{
		nbr /= ft_strlen(base);
		len++;
	}
	return (len);
}

char	*convert_num_to_base(uintptr_t nbr, char *base)
{
	char		*converted_num;
	int			hex_len;
	uintptr_t	unsigned_nbr;

	unsigned_nbr = (uintptr_t)nbr;
	hex_len = get_convnum_len(unsigned_nbr, base);
	converted_num = (char *)ft_calloc((hex_len + 1), sizeof(char));
	if (!converted_num)
		return (NULL);
	if (unsigned_nbr == 0)
	{
		converted_num[0] = '0';
		return (converted_num);
	}
	while (unsigned_nbr > 0)
	{
		converted_num[--hex_len] = base[unsigned_nbr % ft_strlen(base)];
		unsigned_nbr /= ft_strlen(base);
	}
	return (converted_num);
}
