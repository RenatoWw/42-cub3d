/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:49:35 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/20 16:11:40 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_north(t_mlx *mlx, t_texture *tex, t_map *map)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx,
			map->north_texture, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nNorth texture not found.\n");
		mlx_destroy_display(mlx->mlx);
		if (mlx->mlx != NULL)
			free(mlx->mlx);
		if (map->map_grid != NULL)
			free_array(map->map_grid);
		free(map->north_texture);
		free(map->south_texture);
		free(map->east_texture);
		free(map->west_texture);
		exit(1);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	free(map->north_texture);
	map->north_texture = NULL;
}

static void	load_south(t_mlx *mlx, t_texture *tex, t_map *map)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx,
			map->south_texture, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nSouth texture not found.\n");
		if (map->map_grid != NULL)
			free_array(map->map_grid);
		free(map->north_texture);
		free(map->south_texture);
		free(map->east_texture);
		free(map->west_texture);
		mlx_destroy_image(mlx->mlx, map->north.img);
		mlx_destroy_display(mlx->mlx);
		if (mlx->mlx != NULL)
			free(mlx->mlx);
		exit(1);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	free(map->south_texture);
	map->south_texture = NULL;
}

static void	load_west(t_mlx *mlx, t_texture *tex, t_map *map)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx,
			map->west_texture, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nWest texture not found.\n");
		if (map->map_grid != NULL)
			free_array(map->map_grid);
		free(map->north_texture);
		free(map->south_texture);
		free(map->east_texture);
		free(map->west_texture);
		mlx_destroy_image(mlx->mlx, map->north.img);
		mlx_destroy_image(mlx->mlx, map->south.img);
		mlx_destroy_display(mlx->mlx);
		if (mlx->mlx != NULL)
			free(mlx->mlx);
		exit(1);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	free(map->west_texture);
	map->west_texture = NULL;
}

static void	load_east(t_mlx *mlx, t_texture *tex, t_map *map)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx,
			map->east_texture, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nEast texture not found.\n");
		if (map->map_grid != NULL)
			free_array(map->map_grid);
		free(map->north_texture);
		free(map->south_texture);
		free(map->east_texture);
		free(map->west_texture);
		mlx_destroy_image(mlx->mlx, map->north.img);
		mlx_destroy_image(mlx->mlx, map->south.img);
		mlx_destroy_image(mlx->mlx, map->west.img);
		mlx_destroy_display(mlx->mlx);
		if (mlx->mlx != NULL)
			free(mlx->mlx);
		exit(1);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	free(map->east_texture);
	map->east_texture = NULL;
}

void	load_texture(t_mlx *mlx, t_map *map)
{
	mlx->mlx = mlx_init();
	if ((!map->north_texture || !map->south_texture)
		|| (!map->east_texture || !map->west_texture))
	{
		printf("Error\nTexture not found.\n");
		mlx_destroy_display(mlx->mlx);
		if (mlx->mlx != NULL)
			free(mlx->mlx);
		exit(1);
	}
	load_north(mlx, &map->north, map);
	load_south(mlx, &map->south, map);
	load_west(mlx, &map->west, map);
	load_east(mlx, &map->east, map);
}
