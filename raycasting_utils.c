/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:53:57 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/05 19:33:04 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_angle(t_rays *rays)
{
	if (rays->ray_angle < 0)
		rays->ray_angle += 2 * PI;
	if (rays->ray_angle > 2 * PI)
		rays->ray_angle -= 2 * PI;
}

int	is_wall(t_map map, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= map.height)
		return (1);
	if (map_x < 0 || map_x >= map.width)
		return (1);
	if (map.map_grid[map_y][map_x] == 1)
		return (1);
	return (0);
}

double	get_distance(double px, double py, double rx, double ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

void	find_wall_coordinates(t_rays *rays, t_map map)
{
	while (rays->depth_of_field < rays->ray_limit)
	{
		rays->map_x = (int)(rays->ray_x) / 32;
		rays->map_y = (int)(rays->ray_y) / 32;
		if (is_wall(map, rays->map_x, rays->map_y))
			rays->depth_of_field = rays->ray_limit;
		else
		{
			rays->ray_x += rays->offset_x;
			rays->ray_y += rays->offset_y;
			rays->depth_of_field += 1;
		}
	}
}

t_dist	get_wall_distance(t_player *p, t_rays *rays, t_map map, t_point *end)
{
	t_dist	wall_dist;

	check_horizontal_lines(p, rays, map);
	wall_dist.hx = rays->ray_x;
	wall_dist.hy = rays->ray_y;
	wall_dist.dist_h = get_distance(p->pos_x,
			p->pos_y, wall_dist.hx, wall_dist.hy);
	check_vertical_lines(p, rays, map);
	wall_dist.vx = rays->ray_x;
	wall_dist.vy = rays->ray_y;
	wall_dist.dist_v = get_distance(p->pos_x,
			p->pos_y, wall_dist.vx, wall_dist.vy);
	if (wall_dist.dist_h < wall_dist.dist_v)
	{
		end->x = wall_dist.hx;
		end->y = wall_dist.hy;
	}
	else
	{
		end->x = wall_dist.vx;
		end->y = wall_dist.vy;
	}
	return (wall_dist);
}
