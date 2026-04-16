/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lantern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:25:17 by renato            #+#    #+#             */
/*   Updated: 2026/04/16 16:05:05 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_px_color(t_lantern *lantern, char *addr, int x, int y)
{
	char	*pixel_ptr;
	int		offset;

	offset = (y * lantern->line_len) + (x * (lantern->bpp / 8));
	pixel_ptr = addr + offset;
	return (*(unsigned int *)pixel_ptr);
}

static void	init_values(t_lantern *lantern)
{
	if (lantern->is_lantern_on)
		lantern->curr_addr = lantern->addr_lantern_on;
	else
		lantern->curr_addr = lantern->addr_lantern_off;
	lantern->scale_factor = 5;
	lantern->scaled_width = lantern->width * lantern->scale_factor;
	lantern->scaled_height = lantern->height * lantern->scale_factor;
	lantern->start_x = WINDOW_WIDTH - lantern->scaled_width;
	lantern->start_y = WINDOW_HEIGHT - lantern->scaled_height;
}

void	draw_lantern(t_mlx *mlx, t_lantern *lantern)
{
	int				x;
	int				y;
	unsigned int	color;

	if (!lantern->img_lantern_on || !lantern->img_lantern_off)
		return ;
	init_values(lantern);
	y = 0;
	while (y < lantern->scaled_height)
	{
		x = 0;
		while (x < lantern->scaled_width)
		{
			lantern->tex_x = x / lantern->scale_factor;
			lantern->tex_y = y / lantern->scale_factor;
			color = get_px_color(lantern,
					lantern->curr_addr, lantern->tex_x, lantern->tex_y);
			if (color != 0x00FF00FF)
				my_pixel_put(mlx, lantern->start_x + x,
					lantern->start_y + y, color);
			x++;
		}
		y++;
	}
}
