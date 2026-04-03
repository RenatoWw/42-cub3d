/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:14:47 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/02 22:03:23 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include "includes/mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# define PI 3.1415926535

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlx;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
}			t_player;

typedef struct s_map
{
	char	map_grid[10][10];
	int		width;
	int		height;
	int		floor_color;
	int		ceiling_color;
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
}			t_map;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
}			t_game;

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// Minilibx utils functions
void	my_pixel_put(t_mlx *data, int x, int y, int color);
int		close_window(t_mlx *data);
int		key_press(int keycode, t_game *data);
int		key_release(int keycode, t_game *data);

// Drawing functions
int		render_frame(t_game	*data);
void	draw_player(t_mlx *mlx, int pos_x, int pos_y);
void	paint_bg(t_mlx *mlx, int color);

// Init functions
void	init_mlx(t_mlx *mlx);
void	init_player_values(t_game *data);

// Map functions
void	draw_2d_map(t_game *data);
void	draw_map_block(t_game *data, int x_pixel, int y_pixel, int color);
void	init_map(t_map *map);

#endif