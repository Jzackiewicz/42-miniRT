/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:40 by agarbacz          #+#    #+#             */
/*   Updated: 2025/03/25 12:08:00 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/data_processing.h"

// returns -1 on error, 0 on cool name d-_-b
static int	check_extension(const char *filepath)
{
	int			len;
	const char	*ext;

	if (!filepath)
		return (-1);
	ext = ft_strrchr(filepath, '/');
	if (ext)
		ext++;
	if (ext)
		len = ft_strlen(ext);
	else
		len = ft_strlen(filepath);
	if (len < 3)
		return (-1);
	if (ft_strncmp(ext + len - 3, ".rt", 3) == 0)
		return (0);
	return (-1);
}

static void	overwrite_nl(char *line)
{
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
}

static int	handle_empty_line(char *line)
{
	if (!*line)
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	read_and_validate(char *line, char **line_split, int fd,
		t_key_presence *key_presence)
{
	int	objects_status;
	int	settings_status;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		overwrite_nl(line);
		if (handle_empty_line(line))
			continue ;
		line_split = ft_split(line, ' ');
		free(line);
		settings_status = validate_settings(line_split, fd, key_presence);
		if (settings_status == -1)
			return (-1);
		objects_status = validate_objects(line_split, fd, key_presence);
		if (objects_status == -1)
			return (-1);
		if (settings_status == 1 && objects_status == 1)
			return (ft_arr2d_free(line_split), drain_file(fd));
		ft_arr2d_free(line_split);
	}
	return (0);
}

// returns -1 on file error and exits
int	validate_file(char *filepath)
{
	char			*line;
	char			**line_split;
	int				fd;
	t_key_presence	key_presence;
	int				i;

	line = NULL;
	line_split = NULL;
	ft_memset(&key_presence.no_present, 0, sizeof(key_presence.no_present));
	if (check_extension(filepath) == -1)
		return (-1);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit(1);
	if (read_and_validate(line, line_split, fd, &key_presence) != 0)
		return (-1);
	close(fd);
	i = -1;
	while (++i < 6)
	{
		if ((key_presence.no_present[i] != 1 && i < 3))
			return (-1);
	}
	return (0);
}
