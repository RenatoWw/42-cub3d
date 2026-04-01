/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:10:51 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/01 19:50:03 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Desenha uma linha vertical para a parede
void	draw_vline(t_game *game, int x, int draw_start, int draw_end, int color)
{
	int y = draw_start;
	while (y <= draw_end)
	{
		my_pixel_put(game, x, y, color);
		y++;
	}
}

// O Coração do Cub3d: Loop principal de renderização
int	render_frame(t_game *game)
{
	// 1. Limpar a tela pintando Teto e Chão para não deixar rastro [6]
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			if (y < WINDOW_HEIGHT / 2)
				my_pixel_put(game, x, y, 0x00333333); // Teto: Cinza escuro
			else
				my_pixel_put(game, x, y, 0x007A5C3D); // Chão: Marrom
		}
	}

	// 2. Disparar os Raios (O Loop do Eixo X) [1]
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		double ray_dir_x = game->dir_x + game->plane_x * camera_x;
		double ray_dir_y = game->dir_y + game->plane_y * camera_x;

		int map_x = (int)game->pos_x;
		int map_y = (int)game->pos_y;

		double side_dist_x;
		double side_dist_y;

		// A constante de medição [9]
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;
		int side;

		// Calculando o Passo e o Primeiro Pulo (Side Dist) [3]
		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (game->pos_x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (game->pos_y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->pos_y) * delta_dist_y;
		}

		// O Loop do Algoritmo DDA: Caçando a parede [4]
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (worldMap[map_x][map_y] > 0)
				hit = 1;
		}

		// A Distância Perpendicular (evitando o olho de peixe) [10]
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		// Calculando a Altura da Parede na Tela [11]
		int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);

		int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;

		// 3. Renderização [7, 12]
		int color;
		if (worldMap[map_x][map_y] == 1) color = 0x00FF0000; // Vermelho
		else if (worldMap[map_x][map_y] == 2) color = 0x0000FF00; // Verde
		else if (worldMap[map_x][map_y] == 3) color = 0x000000FF; // Azul
		else if (worldMap[map_x][map_y] == 4) color = 0x00FFFFFF; // Branco
		else color = 0x00FFFF00; // Amarelo

		// Se bateu no eixo Y, fazemos a parede ficar mais escura para dar noção de 3D
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F;

		draw_vline(game, x, draw_start, draw_end, color);
	}

	// Joga a imagem renderizada para a janela [8]
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;

	// Inicia Posição e Visão
	game.pos_x = 22.0;
	game.pos_y = 12.0;
	game.dir_x = -1.0;
	game.dir_y = 0.0;
	game.plane_x = 0.0;
	game.plane_y = 0.66;

	// Inicia MiniLibX [8, 13, 14]
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d Lodev");
	game.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);

	// Hooks para manter renderizando e permitir fechar no 'X'
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.window, &esc_handler, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
