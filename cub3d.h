/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:14:47 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/01 19:49:49 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include "includes/mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
}		t_game;

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

void	my_pixel_put(t_game *data, int x, int y, int color);
int		esc_handler(int keycode, t_game *data);
int		close_window(t_game *data);

#endif