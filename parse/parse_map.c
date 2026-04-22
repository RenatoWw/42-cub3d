/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <dapinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:19 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/22 12:13:51 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

static char	**add_line(char **map, char *line)
{
	int		i;
	char	**new;

	i = count_lines(map);
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		new[i] = map[i];
		i++;
	}
	new[i] = ft_strdup(line);
	if (!new[i])
	{
		free(new);
		return (NULL);
	}
	i++;
	new[i] = NULL;
	free(map);
	return (new);
}

void	add_map_line(char *line, t_map *map)
{
	char	**new_map;

	if (!line || line[0] == '\0')
		return ;
	new_map = add_line(map->map_grid, line);
	if (!new_map)
		error_exit_parser("Malloc error while parsing map", map, line, -1);
	map->map_grid = new_map;
}
