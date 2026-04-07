#include "cub3d.h"

static int	count_lines(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

static char	**add_line(char **map, char *line)
{
	int		i;
	char	**new;

	i = count_lines(map);
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit(1);

	i = 0;
	while (map && map[i])
	{
		new[i] = map[i];
		i++;
	}

	new[i++] = ft_strdup(line);
	new[i] = NULL;

	free(map);
	return (new);
}

void	add_map_line(char *line, t_map *map)
{
	map->map_grid = add_line(map->map_grid, line);
}
