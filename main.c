/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:10:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/20 18:24:55 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// invalid rgb range 			-- ok
// missing floor color 			-- ok
// missing ceiling color 		-- ok
// color missing 				-- ok
// color none 					-- ok

// duplicate texture 			-- ok
// missing texture 				-- ok
// empty 						-- ok
// map_only 					-- ok
// player error 				-- ok
// map_missing 					-- segfault e leak

// filetype_missing .cub 		-- mapa carregando
// filetype_wrong .ubc 			-- mapa carregando
// textures not xpm 		 	-- mapa carregando

// sem paredes ou com buraco	-- mapa carregando

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
	data->lantern.img_lantern_on = NULL;
	data->lantern.img_lantern_off = NULL;
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
	if (parse_cub(argv[1], &data.map))
		return (1);
	init_player_values(&data.player);
	if (set_player_position(&data) != 0)
		error_exit_parser("Invalid player.", &data.map, NULL, -1);
	load_texture(&data.mlx, &data.map);
	init_mlx(&data.mlx);
	mlx_loop_hook(data.mlx.mlx, &render_frame, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
