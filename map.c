/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:02:35 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/10 22:56:38 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_block(t_game *data, int x_pixel, int y_pixel, int color)
{
	int	i;
	int	j;
	int	offset_size;

	i = 0;
	offset_size = MAP_OFFSET;
	while (i < offset_size)
	{
		j = 0;
		while (j < offset_size)
		{
			my_pixel_put(&data->mlx, x_pixel + i, y_pixel + j, color);
			j++;
		}
		i++;
	}
}

void	draw_2d_map(t_game *data)
{
	int		x;
	int		y;
	int		color;
	int		row_len;
	char	tile;

	y = 0;
	while (y < data->map.height)
	{
		row_len = (int)ft_strlen(data->map.map_grid[y]);
		x = 0;
		while (x < data->map.width)
		{
			tile = ' ';
			if (x < row_len)
				tile = data->map.map_grid[y][x];
			if (tile == '1')
				color = 0x000000FF;
			else
				color = 0x00000000;
			draw_map_block(data, x * MAP_OFFSET, y * MAP_OFFSET, color);
			x++;
		}
		y++;
	}
}

void	finalize_map(t_map *map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map->map_grid[i])
	{
		if ((int)ft_strlen(map->map_grid[i]) > max)
			max = ft_strlen(map->map_grid[i]);
		i++;
	}
	map->height = i;
	map->width = max;
}

int	is_walkable_tile(t_map map, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= map.height)
		return (0);
	if (map_x < 0 || map_x >= map.width)
		return (0);
	row_len = (int)ft_strlen(map.map_grid[map_y]);
	if (map_x >= row_len)
		return (0);
	return (map.map_grid[map_y][map_x] == '0');
}
