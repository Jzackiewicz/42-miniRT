/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:03:26 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 12:16:19 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_base_str(va_list ptr, char *base)
{
	char			*tmp;
	int				count;
	unsigned int	x;

	x = va_arg(ptr, unsigned int);
	if (!x)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	tmp = convert_num_to_base(x, base);
	count = ft_putstr(tmp);
	free(tmp);
	return (count);
}

int	put_voidptr_hex(va_list ptr, char *base)
{
	char		*tmp;
	int			count;
	uintptr_t	nbr;

	nbr = va_arg(ptr, uintptr_t);
	if (!nbr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	else
	{
		tmp = convert_num_to_base(nbr, base);
		ft_putstr_fd("0x", 1);
		count = ft_putstr(tmp);
		count = count + 2;
		free(tmp);
		return (count);
	}
}

int	put_uint_nbr(va_list ptr)
{
	char	*x;
	char	count;

	x = ft_utoa(va_arg(ptr, unsigned int));
	count = ft_putstr(x);
	free(x);
	return (count);
}

int	ft_putnbr(int n)
{
	char	*nbr;
	char	count;

	nbr = ft_itoa(n);
	count = ft_putstr(nbr);
	free(nbr);
	return (count);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
	return (ft_strlen(s));
}
