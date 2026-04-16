/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lantern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:25:17 by renato            #+#    #+#             */
/*   Updated: 2026/04/15 22:46:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_lantern_pixel_color(t_lantern *lantern, char *addr, int x, int y)
{
	char	*pixel_ptr;
	int		offset;

	offset = (y * lantern->line_len) + (x * (lantern->bpp / 8));
	pixel_ptr = addr + offset;
	return (*(unsigned int *)pixel_ptr);
}

void	draw_lantern(t_game *data)
{
	int				x;
	int				y;
	unsigned int	color;
	char			*current_addr;
	int				screen_x;
	int				screen_y;

	if (!data->lantern.img_lantern_on || !data->lantern.img_lantern_off)
	{
		printf("ERRO: Texturas do lampiao não carregaram!\n");
		return ;
	}
	if (data->lantern.is_lantern_on)
		current_addr = data->lantern.addr_lantern_on;
	else
		current_addr = data->lantern.addr_lantern_off;
	int start_x = WINDOW_WIDTH - data->lantern.width - 20;
	int start_y = WINDOW_HEIGHT - data->lantern.height;
	y = 0;
	while (y < data->lantern.height)
	{
		x = 0;
		while (x < data->lantern.width)
		{
			color = get_lantern_pixel_color(&data->lantern, current_addr, x, y);
			if ((int)color != (int)0xFF00FF && color != (unsigned int)0xFF000000)
			{
				screen_x = start_x + x;
				screen_y = start_y + y;
				if (screen_x >= 0 && screen_x < WINDOW_WIDTH &&
					screen_y >= 0 && screen_y < WINDOW_HEIGHT)
					my_pixel_put(&data->mlx, screen_x, screen_y, color);
			}
			x++;
		}
		y++;
	}
}
