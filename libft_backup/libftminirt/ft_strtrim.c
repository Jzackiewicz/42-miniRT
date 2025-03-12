/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:51:48 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/06 11:15:25 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (c == (char)set[j])
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		end;
	int		start;
	char	*new_string;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	while (end > 0 && is_in_set(s1[end], set))
		end--;
	if (end <= 0)
		return (ft_calloc(1, sizeof(char)));
	new_string = (char *)ft_calloc(((end + 1) - start + 1), sizeof(char));
	if (!new_string)
		return (NULL);
	i = -1;
	while (++i < (end - start + 1))
		new_string[i] = s1[start + i];
	new_string[i] = 0;
	return (new_string);
}

/* int	main(void)
{
	char *x;
	x = ft_strtrim("", "");
	printf("|%s|\n", x);
	free(x);
} */