/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:12:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/04 00:17:27 by renato           ###   ########.fr       */
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

void	init_player_values(t_game *data)
{
	data->player.pos_x = 200.0;
	data->player.pos_y = 200.0;
	data->player.key_w = 0;
	data->player.key_s = 0;
	data->player.key_a = 0;
	data->player.key_d = 0;
	data->player.key_left = 0;
	data->player.key_right = 0;
	data->player.player_angle = 0.0;
	data->player.delta_x = cos(data->player.player_angle) * 0.05;
	data->player.delta_y = sin(data->player.player_angle) * 0.05;
	data->player.move_speed = 0.05;
	data->player.rotation_speed = 0.003;
}
