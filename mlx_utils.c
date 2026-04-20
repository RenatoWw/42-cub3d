/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 23:01:43 by renato            #+#    #+#             */
/*   Updated: 2026/04/20 16:46:07 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	close_window(t_game *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	mlx_destroy_image(data->mlx.mlx, data->map.north.img);
	mlx_destroy_image(data->mlx.mlx, data->map.east.img);
	mlx_destroy_image(data->mlx.mlx, data->map.west.img);
	mlx_destroy_image(data->mlx.mlx, data->map.south.img);
	if (data->lantern.img_lantern_off)
		mlx_destroy_image(data->mlx.mlx, data->lantern.img_lantern_off);
	if (data->lantern.img_lantern_on)
		mlx_destroy_image(data->mlx.mlx, data->lantern.img_lantern_on);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	if (data->mlx.mlx != NULL)
		free(data->mlx.mlx);
	if (data->map.map_grid != NULL)
		free_array(data->map.map_grid);
	exit(0);
}

void	my_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_mlx *mlx, t_point p1, t_point p2, int color)
{
	int		i;
	int		step;
	float	x;
	float	y;

	if (abs(p2.x - p1.x) >= abs(p2.y - p1.y))
		step = abs(p2.x - p1.x);
	else
		step = abs(p2.y - p1.y);
	x = p1.x;
	y = p1.y;
	i = 0;
	while (i <= step)
	{
		my_pixel_put(mlx, round(x), round(y), color);
		x += (p2.x - p1.x) / (float)step;
		y += (p2.y - p1.y) / (float)step;
		i++;
	}
}
