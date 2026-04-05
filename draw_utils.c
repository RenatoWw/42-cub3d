/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:54:04 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/05 17:12:50 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	render_frame(t_game	*data)
{
	set_player_movement(&data->player);
	paint_bg(&data->mlx, 0x00808080);
	draw_2d_map(data);
	draw_rays_2d(&data->player, &data->player.rays, data->map, &data->mlx);
	draw_player(&data->mlx, data->player);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
