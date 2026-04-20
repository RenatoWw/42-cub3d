/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 18:47:34 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/20 18:47:56 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_extension(char *filename, char *extension)
{
	size_t	name_len;
	size_t	ext_len;
	char	*file_ending;

	if (!filename || !extension)
		return (1);
	name_len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (name_len <= ext_len)
		return (1);
	file_ending = filename + (name_len - ext_len);
	if (ft_strncmp(file_ending, extension, ext_len) == 0)
		return (0);
	return (1);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D map.cub\n");
		exit(1);
	}
	if (check_extension(argv[1], ".cub") != 0)
	{
		printf("Error\nInvalid map extension.\n");
		exit(1);
	}
}
