/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarbacz <agarbacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:21:26 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/14 15:25:27 by agarbacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rays.h"

static void	free_tmp(t_intersec **left, t_intersec **right)
{
	free(left);
	free(right);
}

void	merge_arrays(t_intersec **i_s, t_intersec **left_arr,
		t_intersec **right_arr, int *params)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = params[0];
	while (i < params[1] && j < params[2])
	{
		if (left_arr[i]->t < right_arr[j]->t || (compare_floats(left_arr[i]->t,
					right_arr[j]->t) && left_arr[i]->t <= right_arr[j]->t))
			i_s[k++] = left_arr[i++];
		else
			i_s[k++] = right_arr[j++];
	}
	while (i < params[1])
		i_s[k++] = left_arr[i++];
	while (j < params[2])
		i_s[k++] = right_arr[j++];
}

void	merge(t_intersec **i_s, int left, int mid, int right)
{
	int			params[3];
	int			i;
	t_intersec	**left_arr;
	t_intersec	**right_arr;

	params[0] = left;
	params[1] = mid - left + 1;
	params[2] = right - mid;
	left_arr = (t_intersec **)malloc(params[1] * sizeof(t_intersec *));
	if (!left_arr)
		return ;
	right_arr = (t_intersec **)malloc(params[2] * sizeof(t_intersec *));
	if (!right_arr)
	{
		if (left_arr)
			return (free(left_arr));
	}
	i = -1;
	while (++i < params[1])
		left_arr[i] = i_s[left + i];
	i = -1;
	while (++i < params[2])
		right_arr[i] = i_s[mid + 1 + i];
	merge_arrays(i_s, left_arr, right_arr, params);
	free_tmp(left_arr, right_arr);
}

/* Merge sort implementation to sort the intersections array
   by their t values in ascending order
	i_s: the array to sort
	start_index: the start index of the array (most cases: 0)
	end_index: the end index of the array (no_elements - 1) */
void	sort_intersections(t_intersec **i_s, int start_index, int end_index)
{
	int	mid;

	if (start_index < end_index)
	{
		mid = start_index + (end_index - start_index) / 2;
		sort_intersections(i_s, start_index, mid);
		sort_intersections(i_s, mid + 1, end_index);
		merge(i_s, start_index, mid, end_index);
	}
}
