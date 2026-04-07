/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:37:58 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/06 21:57:01 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_horizontal_lines(t_player *player, t_rays *rays, t_map map)
{
	rays->depth_of_field = 0;
	rays->tangent = -1.0 / tan(rays->ray_angle);
	if (rays->ray_angle > PI && rays->ray_angle < 2 * PI)
	{
		rays->ray_y = ((int)(player->pos_y / MAP_OFFSET) * MAP_OFFSET) - 0.0001;
		rays->ray_x = (player->pos_y - rays->ray_y)
			* rays->tangent + player->pos_x;
		rays->offset_y = -MAP_OFFSET;
		rays->offset_x = -rays->offset_y * rays->tangent;
	}
	else if (rays->ray_angle < PI && rays->ray_angle > 0)
	{
		rays->ray_y = ((int)(player->pos_y / 16) * 16) + 16;
		rays->ray_x = (player->pos_y - rays->ray_y)
			* rays->tangent + player->pos_x;
		rays->offset_y = MAP_OFFSET;
		rays->offset_x = -rays->offset_y * rays->tangent;
	}
	else
	{
		rays->ray_x = player->pos_x;
		rays->ray_y = player->pos_y;
		rays->depth_of_field = rays->ray_limit;
	}
	find_wall_coordinates(rays, map);
}

void	check_vertical_lines(t_player *player, t_rays *rays, t_map map)
{
	rays->depth_of_field = 0;
	rays->tangent = -tan(rays->ray_angle);
	if (rays->ray_angle > PI / 2 && rays->ray_angle < (3 * PI / 2))
	{
		rays->ray_x = ((int)(player->pos_x / MAP_OFFSET) * MAP_OFFSET) - 0.0001;
		rays->ray_y = (player->pos_x - rays->ray_x)
			* rays->tangent + player->pos_y;
		rays->offset_x = -MAP_OFFSET;
		rays->offset_y = -rays->offset_x * rays->tangent;
	}
	else if (rays->ray_angle < PI / 2 || rays->ray_angle > (3 * PI / 2))
	{
		rays->ray_x = ((int)(player->pos_x / 16) * 16) + 16;
		rays->ray_y = (player->pos_x - rays->ray_x)
			* rays->tangent + player->pos_y;
		rays->offset_x = MAP_OFFSET;
		rays->offset_y = -rays->offset_x * rays->tangent;
	}
	else
	{
		rays->ray_x = player->pos_x;
		rays->ray_y = player->pos_y;
		rays->depth_of_field = rays->ray_limit;
	}
	find_wall_coordinates(rays, map);
}

void	draw_3d_wall_slice(t_player *player, t_mlx *mlx, int x, double dist)
{
	int		y;
	int		draw_start;
	int		draw_end;
	double	line_height;
	double	diff_angle;

	diff_angle = player->player_angle - player->rays.ray_angle;
	normalize_angle(&diff_angle);
	dist = dist * cos(diff_angle);
	if (dist <= 0.0001)
		dist = 0.0001;
	line_height = ((MAP_OFFSET * WINDOW_HEIGHT) / dist) - 5;
	draw_start = (WINDOW_HEIGHT / 2) - (line_height / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WINDOW_HEIGHT / 2) + (line_height / 2);
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	y = draw_start;
	while (y < draw_end)
	{
		my_pixel_put(mlx, x, y, player->rays.wall_color);
		y++;
	}
}

void	draw_rays_3d(t_player *player, t_rays *rays, t_map map, t_mlx *mlx)
{
	double	angle_step;
	int		i;

	angle_step = (FOV * DR) / WINDOW_WIDTH;
	rays->ray_limit = get_distance(0, 0, map.width, map.height);
	rays->ray_angle = player->player_angle - (DR * (FOV / 2));
	normalize_angle(&rays->ray_angle);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		get_wall_distance(player, rays, map);
		set_wall_color(rays);
		draw_3d_wall_slice(player, mlx, i, rays->wd.dist_t);
		i++;
		rays->ray_angle += angle_step;
		normalize_angle(&rays->ray_angle);
	}
}
