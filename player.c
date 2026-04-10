/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:16:53 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/09 22:05:55 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable_tile(t_map map, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= map.height)
		return (0);
	if (map_x < 0 || map_x >= map.width)
		return (0);
	row_len = (int)ft_strlen(map.map_grid[map_y]);
	if (map_x >= row_len)
		return (0);
	return (map.map_grid[map_y][map_x] == '0');
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

void	move_player(t_player *p, t_map map, double step_x, double step_y)
{
	t_colission	col;

	if (step_x < 0)
		col.x_offset = -2;
	else
		col.x_offset = 2;
	if (step_y < 0)
		col.y_offset = -2;
	else
		col.y_offset = 2;
	col.map_x = (int)(p->pos_x / MAP_OFFSET);
	col.map_y = (int)(p->pos_y / MAP_OFFSET);
	col.map_x_add = (int)((p->pos_x + step_x + col.x_offset) / MAP_OFFSET);
	col.map_y_add = (int)((p->pos_y + step_y + col.y_offset) / MAP_OFFSET);
	if (is_walkable_tile(map, col.map_x_add, col.map_y))
		p->pos_x += step_x;
	if (is_walkable_tile(map, col.map_x, col.map_y_add))
		p->pos_y += step_y;
}

void	set_strafe_keys(t_player *p, t_map map)
{
	double	step_x;
	double	step_y;

	if (p->key_a)
	{
		step_x = cos(p->player_angle - PI / 2) * MOVE_SPEED;
		step_y = sin(p->player_angle - PI / 2) * MOVE_SPEED;
		move_player(p, map, step_x, step_y);
	}
	if (p->key_d)
	{
		step_x = cos(p->player_angle + PI / 2) * MOVE_SPEED;
		step_y = sin(p->player_angle + PI / 2) * MOVE_SPEED;
		move_player(p, map, step_x, step_y);
	}
}

void	set_straight_keys(t_player *p, t_map map)
{
	double	step_x;
	double	step_y;

	step_x = cos(p->player_angle) * MOVE_SPEED;
	step_y = sin(p->player_angle) * MOVE_SPEED;
	if (p->key_w)
		move_player(p, map, step_x, step_y);
	if (p->key_s)
		move_player(p, map, -step_x, -step_y);
}

void	set_player_movement(t_player *p, t_map map)
{
	set_straight_keys(p, map);
	set_strafe_keys(p, map);
	handle_rotation(p);
}
