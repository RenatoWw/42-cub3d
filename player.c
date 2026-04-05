/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:16:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/05 19:34:06 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_mlx *mlx, t_player player)
{
	double	line_x;
	double	line_y;
	int		i;
	int		j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_pixel_put(mlx, player.pos_x + i, player.pos_y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 20)
	{
		line_x = (player.pos_x + 5) + (cos(player.player_angle) * i);
		line_y = (player.pos_y + 5) + (sin(player.player_angle) * i);
		my_pixel_put(mlx, (int)line_x, (int)line_y, 0x00FFFF00);
		i++;
	}
}

void	handle_rotation(t_player *p)
{
	if (p->key_left)
	{
		p->player_angle -= p->rotation_speed;
		if (p->player_angle < 0)
			p->player_angle += 2 * PI;
		p->delta_x = cos(p->player_angle) * p->move_speed;
		p->delta_y = sin(p->player_angle) * p->move_speed;
	}
	if (p->key_right)
	{
		p->player_angle += p->rotation_speed;
		if (p->player_angle > 2 * PI)
			p->player_angle -= 2 * PI;
		p->delta_x = cos(p->player_angle) * p->move_speed;
		p->delta_y = sin(p->player_angle) * p->move_speed;
	}
}

void	set_player_movement(t_player *p)
{
	if (p->key_w)
	{
		p->pos_x += p->delta_x;
		p->pos_y += p->delta_y;
	}
	if (p->key_s)
	{
		p->pos_x -= p->delta_x;
		p->pos_y -= p->delta_y;
	}
	if (p->key_a)
	{
		p->pos_x += cos(p->player_angle - (PI / 2)) * p->move_speed;
		p->pos_y += sin(p->player_angle - (PI / 2)) * p->move_speed;
	}
	if (p->key_d)
	{
		p->pos_x += cos(p->player_angle + (PI / 2)) * p->move_speed;
		p->pos_y += sin(p->player_angle + (PI / 2)) * p->move_speed;
	}
	handle_rotation(p);
}
