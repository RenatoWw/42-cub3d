/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:10:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/01 19:02:16 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	mlx.img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	my_pixel_put(&mlx, 20, 20, 0x00FF0000);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img, 0, 0);
	mlx_key_hook(mlx.window, &esc_handler, &mlx);
	mlx_hook(mlx.window, 17, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
}

int	main(void)
{
	create_window();
	return (0);
}
