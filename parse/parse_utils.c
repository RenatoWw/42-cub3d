/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:55 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/20 19:06:56 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	is_color(char *line)
{
	return (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
		|| *line == 'E' || *line == 'W');
}

char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

void	finalize_all(t_map *map)
{
	if (map->floor_color == -1 || map->ceiling_color == -1)
		error_exit_parser("Missing color.", map, NULL, -1);
	if (!map->north_texture || !map->south_texture
		|| !map->east_texture || !map->west_texture)
		error_exit_parser("Missing wall textures.", map, NULL, -1);
	if (!map->map_grid)
		error_exit_parser("Missing map.", map, NULL, -1);
	validate_map(map);
	finalize_map(map);
}