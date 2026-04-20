/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:47 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/20 18:26:10 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_player_aux(t_game *game, int *found, int i, int j)
{
	if (*found)
		return (1);
	game->player.pos_x = (j * MAP_OFFSET) + (MAP_OFFSET / 2);
	game->player.pos_y = (i * MAP_OFFSET) + (MAP_OFFSET / 2);
	if (game->map.map_grid[i][j] == 'S')
		game->player.player_angle = PI / 2;
	else if (game->map.map_grid[i][j] == 'E')
		game->player.player_angle = PI * 2;
	else if (game->map.map_grid[i][j] == 'N')
		game->player.player_angle = (PI * 3) / 2;
	else if (game->map.map_grid[i][j] == 'W')
		game->player.player_angle = PI;
	game->map.map_grid[i][j] = '0';
	*found = 1;
	return (0);
}

int	set_player_position(t_game *game)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	found = 0;
	while (game->map.map_grid[++i])
	{
		j = 0;
		while (game->map.map_grid[i][j])
		{
			if (game->map.map_grid[i][j] == 'N'
				|| game->map.map_grid[i][j] == 'S'
				|| game->map.map_grid[i][j] == 'E'
				|| game->map.map_grid[i][j] == 'W')
			{
				if (set_player_aux(game, &found, i, j) != 0)
					return (1);
			}
			j++;
		}
	}
	if (!found)
		return (1);
	return (0);
}
