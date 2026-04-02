/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:54:04 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/02 18:04:48 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	close_window(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	if (data->mlx != NULL)
		free(data->mlx);
	exit(0);
}

void	paint_bg(t_mlx *mlx, int color)
{
	int	*pixels;
	int	i;
	int	total_pixels;

	pixels = (int *)mlx->addr;
	total_pixels = WINDOW_WIDTH * WINDOW_HEIGHT;
	i = 0;
	while (i < total_pixels)
	{
		pixels[i] = color;
		i++;
	}
}

void	draw_player(t_mlx *mlx, int pos_x, int pos_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_pixel_put(mlx, pos_x + i, pos_y + j, 0x00FFFF00);
			j++;
		}
		i++;
	}
}

int	render_frame(t_game	*data)
{
	if (data->player.key_w)
		data->player.pos_y -= 0.05;
	if (data->player.key_s)
		data->player.pos_y += 0.05;
	if (data->player.key_a)
		data->player.pos_x -= 0.05;
	if (data->player.key_d)
		data->player.pos_x += 0.05;
	paint_bg(&data->mlx, 0x00808080);
	draw_player(&data->mlx, data->player.pos_x, data->player.pos_y);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
