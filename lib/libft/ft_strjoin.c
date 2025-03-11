/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:37:27 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/07 14:00:03 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_string;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_string = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	i = 0;
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_string[i + s1_len] = s2[i];
		i++;
	}
	new_string[i + s1_len] = 0;
	return (new_string);
}

/* int	main(void)
{
	char x[] = "Dupa";
	char y[] = " Cyce";

	printf("%s\n", ft_strjoin(x, y));
} */