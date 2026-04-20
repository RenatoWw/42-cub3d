/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:50 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/20 15:48:27 by ranhaia-         ###   ########.fr       */
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

void	clean_newline(char *str)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	parse_texture(char *line, t_map *map)
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

t_texture	*get_wall_texture(t_player *p, t_map *map)
{
	if (p->rays.wd.dist_h < p->rays.wd.dist_v)
	{
		if (p->rays.ray_angle > 0 && p->rays.ray_angle < PI)
			return (&map->south);
		return (&map->north);
	}
	else
	{
		if (p->rays.ray_angle > PI / 2 && p->rays.ray_angle < 3 * PI / 2)
			return (&map->west);
		return (&map->east);
	}
}
