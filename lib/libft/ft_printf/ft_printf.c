/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:00:24 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 12:14:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_in_string(char *str, char x)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (x == str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	handle_conversion(char x, va_list ptr)
{
	int	count;

	count = 1;
	if (x == '%')
		ft_putchar_fd('%', 1);
	if (x == 'c')
		ft_putchar_fd((unsigned char)va_arg(ptr, int), 1);
	if (x == 'd' || x == 'i')
		count = ft_putnbr(va_arg(ptr, int));
	if (x == 's')
		count = ft_putstr(va_arg(ptr, char *));
	if (x == 'x')
		count = put_base_str(ptr, "0123456789abcdef");
	if (x == 'X')
		count = put_base_str(ptr, "0123456789ABCDEF");
	if (x == 'p')
		count = put_voidptr_hex(ptr, "0123456789abcdef");
	if (x == 'u')
		count = put_uint_nbr(ptr);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args_ptr;
	size_t	i;
	int		printed_chars;

	printed_chars = 0;
	if (!str)
		return (0);
	i = -1;
	va_start(args_ptr, str);
	while (str[++i])
	{
		if (str[i] == '%' && is_in_string("cspdiuxX%", str[i + 1]))
		{
			printed_chars += handle_conversion(str[i + 1], args_ptr);
			i++;
		}
		else
		{
			printed_chars++;
			ft_putchar_fd(str[i], 1);
		}
	}
	return (printed_chars);
}

/* int	main(void)
{
	char	*s;
	int		x;

	s = "Dupa";
	x = ft_printf("\nx = %X\n", -5654);;
	printf("\nx = %X\n", -5654);
	printf("\n");
	x = printf("Simple test   |%p|", s);
	printf("\nx = %d\n", x);
}
 */