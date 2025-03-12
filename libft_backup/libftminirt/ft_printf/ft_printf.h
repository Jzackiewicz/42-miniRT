/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:54:51 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/23 13:37:45 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*convert_num_to_base(uintptr_t nbr, char *base);
char	*ft_utoa(unsigned int nbr);
int		put_base_str(va_list ptr, char *base);
int		put_voidptr_hex(va_list ptr, char *base);
int		put_uint_nbr(va_list ptr);
int		ft_putnbr(int n);
int		ft_putstr(char *s);
int		ft_printf(const char *str, ...);

#endif
