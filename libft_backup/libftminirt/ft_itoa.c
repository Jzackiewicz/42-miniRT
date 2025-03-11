/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:46:02 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/05 16:27:54 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_nbr_len(int n, int sign)
{
	int				str_len;
	unsigned int	nbr;

	str_len = 1;
	if (n < 0)
		str_len++;
	nbr = (unsigned int)(sign * n);
	while (nbr > 9)
	{
		nbr /= 10;
		str_len++;
	}
	return (str_len);
}

char	*ft_itoa(int n)
{
	char			*new_string;
	int				str_len;
	int				sign;
	unsigned int	nbr;

	sign = 1;
	if (n < 0)
		sign = -1;
	str_len = get_nbr_len(n, sign);
	new_string = (char *)malloc((str_len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	nbr = (unsigned int)(sign * n);
	new_string[str_len] = 0;
	while (str_len)
	{
		str_len--;
		new_string[str_len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign == -1)
		new_string[0] = '-';
	return (new_string);
}

/* int	main(void)
{
	char *x = ft_itoa(42);
	printf("output: %s\n", x);
	free(x);
} */