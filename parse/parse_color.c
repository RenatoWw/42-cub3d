#include "cub3d.h"

int	parse_rgb(char *str)
{
	char	**rgb;

	int r, g, b;
	rgb = ft_split(str, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
		exit(printf("Error\nRGB\n"));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit(printf("Error\nRGB range\n"));
	free_split(rgb);
	return (r << 16 | g << 8 | b);
}

void	parse_color(char *line, t_map *map)
{
	char	**s;

	s = ft_split(line, ' ');
	if (!s[1])
		exit(printf("Error\nColor\n"));
	if (line[0] == 'F')
		map->floor_color = parse_rgb(s[1]);
	else if (line[0] == 'C')
		map->ceiling_color = parse_rgb(s[1]);
	free_split(s);
}
