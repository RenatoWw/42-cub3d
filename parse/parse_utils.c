/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <dapinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:55 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/22 13:50:58 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *line)
{
	while (*line == ' ')
		line++;
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	is_color(char *line)
{
	return (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;

	i = 0;
	has_map_char = 0;
	if (!line || line[0] == '\0')
		return (0);
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1')
			has_map_char = 1;
		else if (line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (has_map_char);
}

char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	return (line);
}

void	finalize_all(t_map *map)
{
	if (map->floor_color == -1 || map->ceiling_color == -1)
		error_exit_parser("Missing color.", map, NULL, -1);
	if (!map->north_texture || !map->south_texture || !map->east_texture
		|| !map->west_texture)
		error_exit_parser("Missing wall textures.", map, NULL, -1);
	if (!map->map_grid)
		error_exit_parser("Missing map.", map, NULL, -1);
	finalize_map(map);
	validate_map(map);
}
