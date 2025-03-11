/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:37 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 13:42:14 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[i] != 0 && i < (size - 1))
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

/* int main()
{
	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);
	size_t x = ft_strlcpy(dest, src, 1);
	printf("%zu - %s\n", x, dest);
	size_t y = strlcpy(dest, src, 1);
	printf("%zu - %s\n", y, dest);
} */