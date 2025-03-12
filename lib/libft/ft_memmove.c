/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:02:46 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/11 15:13:21 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*move(void *dest, char *d, char *s, size_t n)
{
	int		i;

	if (d == NULL && s == NULL)
		return (NULL);
	if (s > d)
	{
		i = 0;
		while (i < (int)n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	return (move(dest, d, s, n));
}

/* int main()
{
	char str1[100];

	strcpy(str1, "123456789");
	memcpy(str1 + 1, str1, 9);
	printf("MEMCPY: %s \n", str1);
	
	strcpy(str1, "123456789");
	memmove(str1 + 1, str1, 9);
	printf("MEMMOVE: %s \n", str1);
	
	strcpy(str1, "123456789");
	ft_memcpy(str1 + 1, str1, 9);
	printf("FT_MEMCPY: %s \n", str1);

	strcpy(str1, "123456789");
	ft_memmove(str1 + 1, str1, 9);
	printf("FT_MEMMOVE: %s \n", str1);

	return 0;
} */
