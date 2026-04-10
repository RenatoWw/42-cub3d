/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:54:04 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/09 21:58:03 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_mlx *mlx, t_player player)
{
	double	line_x;
	double	line_y;
	int		i;
	int		j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_pixel_put(mlx, player.pos_x + i, player.pos_y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 20)
	{
		line_x = (player.pos_x + 5) + (cos(player.player_angle) * i);
		line_y = (player.pos_y + 5) + (sin(player.player_angle) * i);
		my_pixel_put(mlx, (int)line_x, (int)line_y, 0x00FFFF00);
		i++;
	}
}

void	paint_bg(t_mlx *mlx, int floor_color, int ceiling_color)
{
	int	*pixels;
	int	i;
	int	total_pixels;

	pixels = (int *)mlx->addr;
	total_pixels = WINDOW_WIDTH * WINDOW_HEIGHT;
	i = 0;
	while (i < total_pixels)
	{
		if (i < total_pixels / 2)
			pixels[i] = floor_color;
		else
			pixels[i] = ceiling_color;
		i++;
	}
}

void	set_wall_color(t_rays *rays)
{
	if (rays->wd.dist_h > rays->wd.dist_v)
		rays->wall_color = 0x000000FF;
	else
		rays->wall_color = 0x000000CC;
}

int	render_frame(t_game	*data)
{
	set_player_movement(&data->player, data->map);
	paint_bg(&data->mlx, data->map.floor_color, data->map.ceiling_color);
	// draw_rays_3d(&data->player, &data->player.rays, data->map, &data->mlx);
	draw_rays_3d(data);
	draw_2d_map(data);
	draw_player(&data->mlx, data->player);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
