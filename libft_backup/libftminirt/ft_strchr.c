/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:05:06 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/04 10:08:34 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*output;

	output = (char *)s;
	i = 0;
	while (s[i])
	{
		if ((int)output[i] == (char) c)
			return (&output[i]);
		i++;
	}
	if (s[i] == c)
		return (&output[i]);
	return (NULL);
}

/* int main()
{
	printf("%s\n", ft_strchr("Testing", 'z'));
} */