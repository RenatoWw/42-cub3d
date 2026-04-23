/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:18:02 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/23 15:37:47 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_row(char **new_map, int i, int width, char **map)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (j < (int)ft_strlen(map[i]))
			new_map[i][j] = map[i][j];
		else
			new_map[i][j] = ' ';
		j++;
	}
	new_map[i][j] = '\0';
}

static char	**normalize_map(char **map, int height, int width)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_map[i] = malloc(sizeof(char) * (width + 1));
		if (!new_map[i])
		{
			while (i > 0)
				free(new_map[--i]);
			free(new_map);
			return (NULL);
		}
		fill_row(new_map, i, width, map);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static int	find_player(char **map, int height, int *px, int *py)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (map[y][++x])
		{
			if (!is_valid_char(map[y][x]))
				return (1);
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*px = x;
				*py = y;
				player_count++;
			}
		}
	}
	if (player_count != 1)
		return (1);
	return (0);
}

static int	flood_fill(char **map, int x, int y, t_map *m)
{
	int	height;
	int	width;

	height = m->height;
	width = m->width;
	if (x < 0 || y < 0 || y >= height || x >= width)
		return (1);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	map[y][x] = 'F';
	if (flood_fill(map, x + 1, y, m))
		return (1);
	if (flood_fill(map, x - 1, y, m))
		return (1);
	if (flood_fill(map, x, y + 1, m))
		return (1);
	if (flood_fill(map, x, y - 1, m))
		return (1);
	return (0);
}

void	validate_map(t_map *map)
{
	char	**normalized;
	int		px;
	int		py;

	normalized = normalize_map(map->map_grid, map->height, map->width);
	if (!normalized)
		error_exit_parser("Malloc error", map, NULL, -1);
	if (find_player(normalized, map->height, &px, &py) == 1)
	{
		free_array(normalized);
		error_exit_parser("Invalid map or player count", map, NULL, -1);
	}
	if (flood_fill(normalized, px, py, map))
	{
		free_array(normalized);
		error_exit_parser("Map is open.", map, NULL, -1);
	}
	free_array(normalized);
}
