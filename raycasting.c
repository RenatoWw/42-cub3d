/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:37:58 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/09 22:03:15 by renato           ###   ########.fr       */
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

t_texture	*get_wall_texture(t_player *p, t_map *map)
{
	if (p->rays.wd.dist_h < p->rays.wd.dist_v)
	{
		if (p->rays.ray_angle > 0 && p->rays.ray_angle < PI)
			return (&map->south);
		return (&map->north);
	}
	else
	{
		if (p->rays.ray_angle > PI / 2 && p->rays.ray_angle < 3 * PI / 2)
			return (&map->west);
		return (&map->east);
	}
}

void    draw_3d_wall_slice(t_game *data, int x, t_texture *tex, double hit)
{
	int		y;
	int		tex_y;
	double	line_h;
	double	step;
	double	tex_pos;

	data->player.rays.wd.dist_t *= cos(data->player.player_angle
			- data->player.rays.ray_angle);
	if (data->player.rays.wd.dist_t <= 0.0001)
		data->player.rays.wd.dist_t = 0.0001;
	line_h = ((MAP_OFFSET * WINDOW_HEIGHT) / data->player.rays.wd.dist_t);
	y = (WINDOW_HEIGHT / 2) - (line_h / 2);
	if (y < 0)
		y = 0;
	hit = (fmod(fabs(hit), MAP_OFFSET) * tex->width) / MAP_OFFSET;
	if (hit >= tex->width)
		hit = tex->width - 1;
	step = (double)tex->height / line_h;
	tex_pos = (y - (WINDOW_HEIGHT / 2) + (line_h / 2)) * step;
	while (y < (WINDOW_HEIGHT / 2) + (line_h / 2) && y < WINDOW_HEIGHT)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		my_pixel_put(&data->mlx, x, y++, tex->addr[(tex_y * tex->width) + (int)hit]);
		tex_pos += step;
	}
}

void    draw_rays_3d(t_game *data)
{
	double		angle_step;
	double		hit_point;
	int			i;
	t_texture	*tex;

	angle_step = (FOV * DR) / WINDOW_WIDTH;
	data->player.rays.ray_limit = get_distance(0, 0, data->map.width, data->map.height);
	data->player.rays.ray_angle = data->player.player_angle - (DR * (FOV / 2));
	normalize_angle(&data->player.rays.ray_angle);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		get_wall_distance(&data->player, &data->player.rays, data->map);
		tex = get_wall_texture(&data->player, &data->map);
		if (data->player.rays.wd.dist_h < data->player.rays.wd.dist_v)
			hit_point = data->player.rays.wd.hx;
		else
			hit_point = data->player.rays.wd.vy;
		draw_3d_wall_slice(data, i, tex, hit_point);
		data->player.rays.ray_angle += angle_step;
		normalize_angle(&data->player.rays.ray_angle);
		i++;
	}
}

// void	draw_3d_wall_slice(t_player *player, t_mlx *mlx, int x, double dist)
// {
// 	int		y;
// 	int		draw_start;
// 	int		draw_end;
// 	double	line_height;
// 	double	diff_angle;

// 	diff_angle = player->player_angle - player->rays.ray_angle;
// 	normalize_angle(&diff_angle);
// 	dist = dist * cos(diff_angle);
// 	if (dist <= 0.0001)
// 		dist = 0.0001;
// 	line_height = ((MAP_OFFSET * WINDOW_HEIGHT) / dist) - 5;
// 	draw_start = (WINDOW_HEIGHT / 2) - (line_height / 2);
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = (WINDOW_HEIGHT / 2) + (line_height / 2);
// 	if (draw_end >= WINDOW_HEIGHT)
// 		draw_end = WINDOW_HEIGHT - 1;
// 	y = draw_start;
// 	while (y < draw_end)
// 	{
// 		my_pixel_put(mlx, x, y, player->rays.wall_color);
// 		y++;
// 	}
// }

// void	draw_rays_3d(t_player *player, t_rays *rays, t_map map, t_mlx *mlx)
// {
// 	double	angle_step;
// 	int		i;

// 	angle_step = (FOV * DR) / WINDOW_WIDTH;
// 	rays->ray_limit = get_distance(0, 0, map.width, map.height);
// 	rays->ray_angle = player->player_angle - (DR * (FOV / 2));
// 	normalize_angle(&rays->ray_angle);
// 	i = 0;
// 	while (i < WINDOW_WIDTH)
// 	{
// 		get_wall_distance(player, rays, map);
// 		set_wall_color(rays);
// 		draw_3d_wall_slice(player, mlx, i, rays->wd.dist_t);
// 		i++;
// 		rays->ray_angle += angle_step;
// 		normalize_angle(&rays->ray_angle);
// 	}
// }
