/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:10:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/02 18:05:15 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
}

int	main(void)
{
	t_game		data;

	data.player.pos_x = 200.0;
	data.player.pos_y = 200.0;
	data.player.key_w = 0;
	data.player.key_s = 0;
	data.player.key_a = 0;
	data.player.key_d = 0;
	init_mlx(&data.mlx);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data.mlx);
	mlx_loop(data.mlx.mlx);
	return (0);
}
