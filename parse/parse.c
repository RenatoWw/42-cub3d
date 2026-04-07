/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <dapinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:59 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/07 10:18:24 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

int	parse_cub(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nFile\n"), 1);
	while ((line = get_next_line(fd)))
	{
		line = trim_newline(line);
		if (is_texture(line))
			parse_texture(line, map);
		else if (is_color(line))
			parse_color(line, map);
		else if (is_map_line(line))
			add_map_line(line, map);
		free(line);
	}
	close(fd);
	finalize_map(map);
	validate_map(map);
	return (0);
}
