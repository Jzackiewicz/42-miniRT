/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:55:13 by jzack	iew          #+#    #+#           */
/*   Updated: 2024/12/07 11:48:40 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*data;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb && (nmemb * size) / nmemb != size)
		return (NULL);
	data = (void *)malloc(nmemb * size);
	if (!data)
		return (NULL);
	ft_bzero(data, nmemb * size);
	return (data);
}
