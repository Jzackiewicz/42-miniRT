/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:52:05 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 14:12:26 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	while (n-- > 0)
		d[n] = s[n];
	return (dest);
}

/* int main()
{
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};
	char s4[] = {};
	ft_memcpy(s2, s4, 4);
	for (int i = 0; i < 4; i++)
	{
		printf("%d ", s2[i]);
	}
	printf("\n%s", s2);

} */