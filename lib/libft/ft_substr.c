/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:21:42 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/06 11:13:45 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	static char		*new_string;
	unsigned int	i;
	size_t			new_len;

	if (!s || !len)
		return ((char *)ft_calloc(1, 1));
	if (start > ft_strlen(s))
		return ((char *)ft_calloc(1, 1));
	new_len = ft_strlen(&s[start]) + 1;
	if (len < new_len)
		new_len = len + 1;
	new_string = (char *)ft_calloc(new_len, sizeof(char));
	if (!new_string)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len && start <= ft_strlen(s))
	{
		new_string[i] = s[start + i];
		i++;
	}
	return (new_string);
}

/* int main()
{
	char	*x;
	x = ft_substr("tripouille", 3, 2);
	printf("|%s|\n", x);
	free(x);
} */