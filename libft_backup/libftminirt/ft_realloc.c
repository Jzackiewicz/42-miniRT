/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:56:40 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/31 14:41:04 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	memcpy(new, ptr, copy_size);
	free(ptr);
	return (new);
}
