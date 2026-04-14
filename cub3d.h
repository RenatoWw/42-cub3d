/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranhaia- <ranhaia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:14:47 by ranhaia-          #+#    #+#             */
/*   Updated: 2026/04/14 16:50:57 by ranhaia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes/libft/libft.h"
# include "includes/mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# define PI 3.1415926535
# define DR 0.0174533
# define FOV 60
# define MAP_OFFSET 16
# define MOVE_SPEED 0.07
# define ROTATION_SPEED 0.0025
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_dist
{
	double		hx;
	double		hy;
	double		vx;
	double		vy;
	double		dist_h;
	double		dist_v;
	double		dist_t;
	double		line_height;
}				t_dist;

typedef struct s_rays
{
	int			rays;
	int			map_x;
	int			map_y;
	int			depth_of_field;
	int			ray_limit;
	int			wall_color;
	double		ray_angle;
	double		ray_x;
	double		ray_y;
	double		offset_x;
	double		offset_y;
	double		tangent;
	t_dist		wd;
}				t_rays;

typedef struct s_collision
{
	int			x_offset;
	int			y_offset;
	int			map_x;
	int			map_y;
	int			map_x_add;
	int			map_x_sub;
	int			map_y_add;
	int			map_y_sub;
	double		step_x;
	double		step_y;
}				t_colission;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		delta_x;
	double		delta_y;
	double		player_angle;
	double		move_speed;
	double		rotation_speed;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	t_rays		rays;
}				t_player;

typedef struct s_point
{
	int			x;
	int			y;
	int			color;
}				t_point;

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}			t_texture;

typedef struct s_map
{
	char		**map_grid;
	int			width;
	int			height;

	int			floor_color;
	int			ceiling_color;

	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;

	t_texture	north;
	t_texture	east;
	t_texture	west;
	t_texture	south;
}				t_map;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_map		map;
}				t_game;

// Minilibx utils functions
void			my_pixel_put(t_mlx *data, int x, int y, int color);
int				close_window(t_game *data);
int				key_press(int keycode, t_game *data);
int				key_release(int keycode, t_game *data);
int				mouse_move(int x, int y, t_game *data);

// Drawing functions
int				render_frame(t_game *data);
int				render_frame_bonus(t_game *data);
void			paint_bg(t_mlx *mlx, int floor_color, int ceiling_color);
void			draw_line(t_mlx *mlx, t_point p1, t_point p2, int color);

// Init functions
void			init_mlx(t_mlx *mlx);
void			init_player_values(t_player *player);

// Map functions
void			draw_2d_map(t_game *data);
void			draw_map_block(t_game *data, int x_pixel, int y_pixel,
					int color);
void			finalize_map(t_map *map);

// Player functions
void			set_player_movement(t_player *p, t_map map);
void			handle_rotation(t_player *p);
void			draw_player(t_mlx *mlx, t_player player);
int				is_walkable_tile(t_map map, int map_x, int map_y);

// Raycasting
void			draw_rays_3d(t_game *data);
double			get_distance(double px, double py, double rx, double ry);
int				is_wall(t_map map, int map_x, int map_y);
void			find_wall_coordinates(t_rays *rays, t_map map);
t_dist			get_wall_distance(t_player *p, t_rays *rays, t_map map);
void			check_vertical_lines(t_player *player, t_rays *rays, t_map map);
void			check_horizontal_lines(t_player *player, t_rays *rays,
					t_map map);
void			normalize_angle(double *angle);

// -----------------PARSE------------------------- //
// parse.c
int				parse_cub(char *file, t_map *map, t_mlx *mlx);

// color
int				parse_rgb(char *str);
void			parse_color(char *line, t_map *map);

// parse_map
void			add_map_line(char *line, t_map *map);

// parse_player
void			set_player_position(t_game *game);
// parse_texture
void			free_split(char **split);
void			parse_texture(char *line, t_map *map, t_mlx *mlx);
t_texture		*get_wall_texture(t_player *p, t_map *map);

// parse_utils
int				is_texture(char *line);
int				is_color(char *line);
int				is_map_line(char *line);
char			*trim_newline(char *line);

// validate_map
void			validate_map(t_map *map);
#endif
