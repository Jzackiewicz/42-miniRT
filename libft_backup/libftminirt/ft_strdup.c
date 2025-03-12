/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:17:43 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/04 17:36:51 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		strlen;
	char	*new_string;

	strlen = ft_strlen(s);
	new_string = (char *)malloc((strlen + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	new_string = ft_memcpy(new_string, s, (strlen + 1));
	return ((char *)new_string);
}

/* int main()
{
	char x[20] = "Testingggg";
	char *y;

	y = ft_strdup(x);
	printf("%s", y);
} */