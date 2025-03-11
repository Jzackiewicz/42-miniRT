/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstr_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:50:06 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/12 11:17:32 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2dstr_realloc(char **arr, size_t old_rows, size_t new_rows)
{
	char	**new_arr;
	size_t	i;

	if (!arr || !*arr)
		return (NULL);
	new_arr = (char **)ft_calloc(new_rows, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_rows && i < new_rows)
	{
		new_arr[i] = arr[i];
		i++;
	}
	if (new_rows < old_rows)
		while (arr[i])
			free(arr[i++]);
	free(arr);
	return (new_arr);
}
