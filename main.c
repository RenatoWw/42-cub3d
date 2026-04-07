/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:10:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/06 21:28:19 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_game		data;

	init_player_values(&data.player);
	init_mlx(&data.mlx);
	init_map(&data.map);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, 6, 1L << 6, mouse_move, &data);
	mlx_mouse_hide(data.mlx.mlx, data.mlx.win);
	mlx_mouse_move(data.mlx.mlx, data.mlx.win,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data.mlx);
	mlx_loop(data.mlx.mlx);
	return (0);
}
