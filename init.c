/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:12:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/14 16:41:21 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
}

void	init_player_values(t_player *player)
{
	player->key_w = 0;
	player->key_s = 0;
	player->key_a = 0;
	player->key_d = 0;
	player->key_left = 0;
	player->key_right = 0;
	player->move_speed = MOVE_SPEED;
	player->rotation_speed = ROTATION_SPEED;
}
