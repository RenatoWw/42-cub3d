/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:50 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/09 21:58:33 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	load_texture(t_mlx *mlx, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nTexture not found.\n");
		close_window(mlx);
	}
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}

void	clean_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	parse_texture(char *line, t_map *map, t_mlx *mlx)
{
	char	**s;

	s = ft_split(line, ' ');
	if (!s || !s[1])
	{
		printf("Error\nInvalid texture\n");
		if (s)
			free_split(s);
		exit(1);
	}
	clean_newline(s[1]);
	if (!ft_strncmp(s[0], "NO", 3))
		load_texture(mlx, &map->north, s[1]);
	else if (!ft_strncmp(s[0], "SO", 3))
		load_texture(mlx, &map->south, s[1]);
	else if (!ft_strncmp(s[0], "WE", 3))
		load_texture(mlx, &map->west, s[1]);
	else if (!ft_strncmp(s[0], "EA", 3))
		load_texture(mlx, &map->east, s[1]);
	free_split(s);
}
