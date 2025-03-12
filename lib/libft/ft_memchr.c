/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:26:47 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 12:59:47 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*output;

	output = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (output[i] == (unsigned char)c)
			return ((char *)&output[i]);
		i++;
	}
	return (NULL);
}

/* int main()
{
	char	s[] = {0, 1, 2, 3, 4, 5};

	printf("%d\n", ft_memchr(s, 2, 3));
}
 */