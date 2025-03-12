/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:16:14 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 13:29:26 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		p[n - 1] = (unsigned char) c;
		n--;
	}
	return (s);
}

/* int main()
{
	char str[20] = "aaaabbbbbbsssss";
	ft_memset(str, '+', 4);
	printf("%s", str);
} */