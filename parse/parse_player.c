/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:47 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/07 20:08:59 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_aux(t_game *game, int *found, int i, int j)
{
	if (*found)
		exit(printf("Error\nMultiple players\n"));
	game->player.pos_x = j * MAP_OFFSET;
	game->player.pos_y = i * MAP_OFFSET;
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
}

void	set_player_position(t_game *game)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	while (game->map.map_grid[i])
	{
		j = 0;
		while (game->map.map_grid[i][j])
		{
			if (game->map.map_grid[i][j] == 'N'
				|| game->map.map_grid[i][j] == 'S'
				|| game->map.map_grid[i][j] == 'E'
				|| game->map.map_grid[i][j] == 'W')
			{
				set_player_aux(game, &found, i, j);
			}
			j++;
		}
		i++;
	}
	if (!found)
		exit(printf("Error\nNo player\n"));
}
