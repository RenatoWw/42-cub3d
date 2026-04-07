/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:53:57 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/07 17:46:07 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * PI;
	while (*angle > 2 * PI)
		*angle -= 2 * PI;
}

int	is_wall(t_map map, int map_x, int map_y)
{
	// int	row_len;

	if (map_y < 0 || map_y >= map.height)
		return (1);
	if (map_x < 0 || map_x >= map.width)
		return (1);
	// row_len = (int)ft_strlen(map.map_grid[map_y]);
	// if (map_x >= row_len)
	// 	return (1);
	if (map.map_grid[map_y][map_x] == '1' || map.map_grid[map_y][map_x] == ' ')
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
		rays->map_x = (int)(rays->ray_x) / MAP_OFFSET;
		rays->map_y = (int)(rays->ray_y) / MAP_OFFSET;
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

t_dist	get_wall_distance(t_player *p, t_rays *rays, t_map map)
{
	check_horizontal_lines(p, rays, map);
	rays->wd.hx = rays->ray_x;
	rays->wd.hy = rays->ray_y;
	rays->wd.dist_h = get_distance(p->pos_x,
			p->pos_y, rays->wd.hx, rays->wd.hy);
	check_vertical_lines(p, rays, map);
	rays->wd.vx = rays->ray_x;
	rays->wd.vy = rays->ray_y;
	rays->wd.dist_v = get_distance(p->pos_x,
			p->pos_y, rays->wd.vx, rays->wd.vy);
	if (rays->wd.dist_h < rays->wd.dist_v)
		rays->wd.dist_t = rays->wd.dist_h;
	else
		rays->wd.dist_t = rays->wd.dist_v;
	return (rays->wd);
}
