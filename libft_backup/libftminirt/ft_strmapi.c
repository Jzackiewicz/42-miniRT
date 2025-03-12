/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:36:26 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/06 13:24:04 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_string;
	unsigned int	i;
	int				strlen;

	if (!s)
		return (NULL);
	i = 0;
	strlen = ft_strlen(s);
	new_string = (char *)ft_calloc((strlen + 1), sizeof(char));
	if (!new_string)
		return (NULL);
	while (s[i])
	{
		new_string[i] = f(i, s[i]);
		i++;
	}
	return (new_string);
}

/* int main()
{
	char s[] = "teStinG";
	char *x = ft_strmapi(s, ft_tou)
} */