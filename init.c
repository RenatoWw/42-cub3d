/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:12:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/15 22:24:41 by renato           ###   ########.fr       */
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

void	init_lantern(t_game *data)
{
	data->lantern.img_lantern_off = mlx_xpm_file_to_image(data->mlx.mlx,
			"textures/imagens_game/lamp_off.xpm",
			&data->lantern.width, &data->lantern.height);
	data->lantern.img_lantern_on = mlx_xpm_file_to_image(data->mlx.mlx,
			"textures/imagens_game/lamp_on.xpm",
			&data->lantern.width, &data->lantern.height);
	data->lantern.addr_lantern_off = mlx_get_data_addr(
			data->lantern.img_lantern_off, &data->lantern.bpp,
			&data->lantern.line_len, &data->lantern.endian);
	data->lantern.addr_lantern_on = mlx_get_data_addr(
			data->lantern.img_lantern_on, &data->lantern.bpp,
			&data->lantern.line_len, &data->lantern.endian);
}
