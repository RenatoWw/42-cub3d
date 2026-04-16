/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:10:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/15 22:17:11 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *data)
{
	data->map.map_grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.floor_color = -1;
	data->map.ceiling_color = -1;
	data->map.north_texture = NULL;
	data->map.south_texture = NULL;
	data->map.east_texture = NULL;
	data->map.west_texture = NULL;
	data->lantern.is_lantern_on = 0;
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D map.cub\n");
		return (1);
	}
	init_game(&data);
	init_player_values(&data.player);
	init_mlx(&data.mlx);
	if (parse_cub(argv[1], &data.map, &data.mlx))
		return (1);
	set_player_position(&data);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
