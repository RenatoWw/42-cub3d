/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 23:01:43 by renato            #+#    #+#             */
/*   Updated: 2026/04/05 19:26:12 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	if (data->mlx != NULL)
		free(data->mlx);
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
