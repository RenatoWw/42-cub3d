/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:59 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/23 14:25:41 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	parse_config_line(char *line, t_map *map, int fd)
{
	if (is_texture(line))
	{
		if (parse_texture(line, map) != 0)
			error_exit_parser("Invalid texture", map, line, fd);
	}
	else if (is_color(line))
	{
		if (parse_color(line, map) != 0)
			error_exit_parser("Invalid RGB", map, line, fd);
	}
	else if (*line != '\0')
		error_exit_parser("Invalid config line", map, line, fd);
}

static int	is_only_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	parse_line(int fd, t_map *map)
{
	char	*line;
	int		map_started;

	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = trim_newline(line);
		if (is_map_line(line))
		{
			map_started = 1;
			add_map_line(line, map);
		}
		else if (!map_started)
			parse_config_line(line, map, fd);
		else if (!is_only_whitespace(line))
			error_exit_parser("Invalid content after map", map, line, fd);
		free(line);
	}
}

int	parse_cub(char *file, t_map *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nFile\n"), 1);
	parse_line(fd, map);
	close(fd);
	if (!map->map_grid)
		error_exit_parser("Map missing", map, NULL, -1);
	finalize_all(map);
	return (0);
}
