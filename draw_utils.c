/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:54:04 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/06 17:13:37 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		rays->wall_color = 0x00FF0000;
	else
		rays->wall_color = 0x00CC0000;
}

int	render_frame(t_game	*data)
{
	set_player_movement(&data->player);
	paint_bg(&data->mlx, 0x00808080, 0x00404040);
	draw_rays_3d(&data->player, &data->player.rays, data->map, &data->mlx);
	draw_2d_map(data);
	draw_player(&data->mlx, data->player);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
