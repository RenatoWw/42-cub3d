/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <dapinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:59 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/22 13:50:50 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

static void	clean_gnl(int fd)
{
	char	*temp;

	if (fd >= 0)
	{
		while (1)
		{
			temp = get_next_line(fd);
			if (!temp)
				break ;
			free(temp);
		}
		close(fd);
	}
}

void	error_exit_parser(char *error_msg, t_map *map, char *curr_line, int fd)
{
	printf("Error\n%s\n", error_msg);
	if (curr_line)
		free(curr_line);
	clean_gnl(fd);
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->map_grid)
		free_array(map->map_grid);
	exit(1);
}

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

int	parse_cub(char *file, t_map *map)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nFile\n"), 1);
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
	close(fd);
	if (!map->map_grid)
		error_exit_parser("Map missing", map, NULL, -1);
	finalize_all(map);
	return (0);
}
