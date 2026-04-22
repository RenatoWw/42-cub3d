/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <dapinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:18:02 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/22 13:51:08 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static char	**normalize_map(char **map, int height, int width)
{
	char	**new_map;
	int		i;
	int		j;

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
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static void	find_player(char **map, int height, int *px, int *py, t_map *orig)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_char(map[y][x]))
				error_exit_parser("Invalid character in map", orig, NULL, -1);
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*px = x;
				*py = y;
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_exit_parser("Invalid player count", orig, NULL, -1);
}

static int	flood_fill(char **map, int x, int y, int width, int height)
{
	if (x < 0 || y < 0 || y >= height || x >= width)
		return (1);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	map[y][x] = 'F';
	if (flood_fill(map, x + 1, y, width, height))
		return (1);
	if (flood_fill(map, x - 1, y, width, height))
		return (1);
	if (flood_fill(map, x, y + 1, width, height))
		return (1);
	if (flood_fill(map, x, y - 1, width, height))
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
	find_player(normalized, map->height, &px, &py, map);
	if (flood_fill(normalized, px, py, map->width, map->height))
	{
		free_array(normalized);
		error_exit_parser("Map is open.", map, NULL, -1);
	}
	free_array(normalized);
}
