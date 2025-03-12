/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:47:43 by jzackiew          #+#    #+#             */
/*   Updated: 2024/12/09 08:49:31 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*buffer;

	if (!lst || !f)
		return ;
	buffer = lst;
	while (buffer)
	{
		f(buffer->content);
		buffer = buffer->next;
	}
}
