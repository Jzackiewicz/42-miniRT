/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:12:52 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 13:51:25 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*output;
	int		str_len;

	output = (char *)s;
	str_len = (int)ft_strlen(s);
	while (str_len >= 0)
	{
		if (output[str_len] == (char)c)
			return (&output[str_len]);
		str_len--;
	}
	return (NULL);
}

/* int main()
{
	char s[] = "tripouille";
	printf("%c\n", 't'+256);
	printf("%s\n", ft_strrchr(s, 't' + 256));
} */