/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:02:35 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/03 22:18:49 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	static char	temp_map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	map->width = 10;
	map->height = 10;
	ft_memcpy(map->map_grid, temp_map, sizeof(temp_map));
}

void	draw_map_block(t_game *data, int x_pixel, int y_pixel, int color)
{
	int	i;
	int	j;
	int	offset_size;

	i = 0;
	offset_size = 32;
	while (i < offset_size - 1)
	{
		j = 0;
		while (j < offset_size - 1)
		{
			my_pixel_put(&data->mlx, x_pixel + i, y_pixel + j, color);
			j++;
		}
		i++;
	}
}

void	draw_2d_map(t_game *data)
{
	int	x;
	int	y;
	int	color;
	int	offset_size;

	y = 0;
	offset_size = 32;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map_grid[y][x] == 1)
				color = 0x00FFFFFF;
			else
				color = 0x00000000;
			draw_map_block(data, x * offset_size, y * offset_size, color);
			x++;
		}
		y++;
	}
}
