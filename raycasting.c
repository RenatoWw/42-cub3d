/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:37:58 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/05 19:32:30 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_horizontal_lines(t_player *player, t_rays *rays, t_map map)
{
	rays->depth_of_field = 0;
	rays->tangent = -1.0 / tan(rays->ray_angle);
	if (rays->ray_angle > PI && rays->ray_angle < 2 * PI)
	{
		rays->ray_y = ((int)(player->pos_y / 32) * 32) - 0.0001;
		rays->ray_x = (player->pos_y - rays->ray_y)
			* rays->tangent + player->pos_x;
		rays->offset_y = -32;
		rays->offset_x = -rays->offset_y * rays->tangent;
	}
	else if (rays->ray_angle < PI && rays->ray_angle > 0)
	{
		rays->ray_y = ((int)(player->pos_y / 32) * 32) + 32;
		rays->ray_x = (player->pos_y - rays->ray_y)
			* rays->tangent + player->pos_x;
		rays->offset_y = 32;
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
		rays->ray_x = ((int)(player->pos_x / 32) * 32) - 0.0001;
		rays->ray_y = (player->pos_x - rays->ray_x)
			* rays->tangent + player->pos_y;
		rays->offset_x = -32;
		rays->offset_y = -rays->offset_x * rays->tangent;
	}
	else if (rays->ray_angle < PI / 2 || rays->ray_angle > (3 * PI / 2))
	{
		rays->ray_x = ((int)(player->pos_x / 32) * 32) + 32;
		rays->ray_y = (player->pos_x - rays->ray_x)
			* rays->tangent + player->pos_y;
		rays->offset_x = 32;
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

void	draw_rays_2d(t_player *player, t_rays *rays, t_map map, t_mlx *mlx)
{
	t_dist	wall_dist;
	t_point	start;
	t_point	end;
	int		i;

	rays->ray_limit = get_distance(0, 0, map.width, map.height);
	rays->ray_angle = player->player_angle - (DR * (FOV / 2));
	normalize_angle(rays);
	i = 0;
	while (i < FOV)
	{
		wall_dist = get_wall_distance(player, rays, map, &end);
		start.x = player->pos_x + 5;
		start.y = player->pos_y + 5;
		if (wall_dist.dist_h < wall_dist.dist_v)
			draw_line(mlx, start, end, 0x0000FF00);
		else
			draw_line(mlx, start, end, 0x0000FF00);
		i++;
		rays->ray_angle += DR;
		normalize_angle(rays);
	}
}
