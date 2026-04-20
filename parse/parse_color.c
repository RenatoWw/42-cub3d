/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:17:34 by dapinhei          #+#    #+#             */
/*   Updated: 2026/04/20 18:00:04 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_rgb(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		if (rgb)
			free_split(rgb);
		return (-1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

int	parse_color(char *line, t_map *map)
{
	char	**s;
	int		color;

	s = ft_split(line, ' ');
	if (!s || !s[1])
	{
		if (s)
			free_split(s);
		return (1);
	}
	color = parse_rgb(s[1]);
	free_split(s);
	if (color == -1)
		return (1);
	if (line[0] == 'F')
		map->floor_color = color;
	else if (line[0] == 'C')
		map->ceiling_color = color;
	return (0);
}
