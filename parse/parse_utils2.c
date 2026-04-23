/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:11:15 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/23 15:32:59 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static void	clean_gnl(int fd)
{
	char	*temp;

	if (fd >= 0)
	{
		while (1)
		{
			temp = get_next_line(fd);
			if (!temp)
				break ;
			free(temp);
		}
		close(fd);
	}
}

void	error_exit_parser(char *error_msg, t_map *map, char *curr_line, int fd)
{
	printf("Error\n%s\n", error_msg);
	if (curr_line)
		free(curr_line);
	clean_gnl(fd);
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->map_grid)
		free_array(map->map_grid);
	exit(1);
}
