#include "cub3d.h"

int	is_texture(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	is_color(char *line)
{
	return (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
		|| *line == 'E' || *line == 'W');
}

char	*trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
