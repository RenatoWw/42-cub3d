#include "cub3d.h"

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
				if (found)
					exit(printf("Error\nMultiple players\n"));

				game->player.pos_x = j * MAP_OFFSET;
				game->player.pos_y = i * MAP_OFFSET;

				game->map.map_grid[i][j] = '0';
				found = 1;
			}
			j++;
		}
		i++;
	}

	if (!found)
		exit(printf("Error\nNo player\n"));
}
