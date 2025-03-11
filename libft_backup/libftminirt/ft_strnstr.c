/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:39:00 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 13:50:49 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (!little || *little == 0)
		return ((char *)big);
	little_len = ft_strlen(little);
	i = 0;
	while (big[i] != 0 && len != 0)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && (i + j) < len)
		{
			if (j == little_len - 1)
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/* int main()
{
	char haystack[] = "aaabcabcd";
	char needle[] = "aabc";
	char * empty = (char*)"";

	printf("%s\n", ft_strnstr(haystack, "cd", 9));
} */