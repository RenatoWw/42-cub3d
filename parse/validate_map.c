/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinhei <dapinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:18:02 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/07 10:18:03 by dapinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

void	validate_map(t_map *map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map->map_grid[i])
	{
		j = 0;
		while (map->map_grid[i][j])
		{
			if (!is_valid_char(map->map_grid[i][j]))
				exit(printf("Error\nInvalid char\n"));
			if (ft_strchr("NSEW", map->map_grid[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		exit(printf("Error\nPlayer\n"));
}
