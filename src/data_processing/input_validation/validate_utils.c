/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:19:50 by agarbacz          #+#    #+#             */
/*   Updated: 2025/04/17 17:48:03 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

int	clean_on_error(char **line_split)
{
	if (line_split)
		ft_arr2d_free(line_split);
	return (-1);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_float(const char *str)
{
	int	i;
	int	has_dot;
	int	has_digit;

	i = -1;
	has_dot = 0;
	has_digit = 0;
	if (!str || !*str)
		return (0);
	while (str[++i])
	{
		if (!i && (str[i] == '+' || str[i] == '-'))
			continue ;
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		else
			has_digit = 1;
	}
	return (has_digit);
}

/* utility which reads the file to the end with gnl()
	on encountered error in parsing/validation
		to prevent memory leaks */
int	drain_file(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (-1);
		free(line);
	}
	close(fd);
	return (-1);
}

int	validate_texture_file(const char *path)
{
	int texture_fd;

	texture_fd = open(path, O_RDONLY);
	if (texture_fd < 0)
		return (1);
	close(texture_fd);
	return (0);
}