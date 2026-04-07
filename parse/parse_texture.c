#include "cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	parse_texture(char *line, t_map *map)
{
	char	**s;

	s = ft_split(line, ' ');
	if (!s[1])
		exit(printf("Error\nTexture\n"));
	if (!ft_strncmp(s[0], "NO", 2))
		map->north_texture = ft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "SO", 2))
		map->south_texture = ft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "WE", 2))
		map->west_texture = ft_strdup(s[1]);
	else if (!ft_strncmp(s[0], "EA", 2))
		map->east_texture = ft_strdup(s[1]);
	free_split(s);
}
