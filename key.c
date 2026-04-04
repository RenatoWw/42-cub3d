/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:49:40 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/03 23:37:37 by renato           ###   ########.fr       */
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
