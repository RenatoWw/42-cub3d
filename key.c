/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:49:40 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/06 18:27:21 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *data)
{
	if (keycode == 65307)
		close_window(&data->mlx);
	if (keycode == 119)
		data->player.key_w = 1;
	else if (keycode == 115)
		data->player.key_s = 1;
	else if (keycode == 97)
		data->player.key_a = 1;
	else if (keycode == 100)
		data->player.key_d = 1;
	else if (keycode == 65361)
		data->player.key_left = 1;
	else if (keycode == 65363)
		data->player.key_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *data)
{
	if (keycode == 119)
		data->player.key_w = 0;
	else if (keycode == 115)
		data->player.key_s = 0;
	else if (keycode == 97)
		data->player.key_a = 0;
	else if (keycode == 100)
		data->player.key_d = 0;
	else if (keycode == 65361)
		data->player.key_left = 0;
	else if (keycode == 65363)
		data->player.key_right = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *data)
{
	int		delta_x;
	double	sensitivity;

	(void)y;
	if (x == WINDOW_WIDTH / 2)
		return (0);
	sensitivity = ROTATION_SPEED;
	delta_x = x - (WINDOW_WIDTH / 2);
	data->player.player_angle += delta_x * sensitivity;
	normalize_angle(&data->player.player_angle);
	data->player.delta_x = cos(data->player.player_angle)
		* data->player.move_speed;
	data->player.delta_y = sin(data->player.player_angle)
		* data->player.move_speed;
	mlx_mouse_move(data->mlx.mlx, data->mlx.win,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	return (0);
}
