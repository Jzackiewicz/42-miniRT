/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:11 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 11:55:38 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2d_strdup(char **arr)
{
	int		i;
	int		arr_len;
	char	**new_arr;

	if (!arr)
		return (NULL);
	arr_len = ft_2d_strlen(arr);
	i = 0;
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!new_arr)
		return (NULL);
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = 0;
	return (new_arr);
}
