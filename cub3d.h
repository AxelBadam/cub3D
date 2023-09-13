/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/13 14:43:28 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1440
# define HEIGHT 960
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_map
{
	int			map_s;
	int			map_x;
	int			map_y;
	int			*map;
	char		*path_to_north;
	char		*path_to_south;
	char		*path_to_west;
	char		*path_to_east;
	int			floor_color;
	int			cealing_color;
	float		map_postion_x;
	float		map_postion_y;
	int			f_color_check;
	int			c_color_check;
}	t_map;

typedef struct s_player
{
	int		og_y;
	int		og_x;
	float	py;
	float	px;
	float	dx;
	float	dy;
	float	pa;
}	t_player;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		side;
	int		vmt;
	int		hmt;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dis_v;
	float	dis_h;
	float	tan;
	float	len;
	float	flag_h;
}	t_ray;

typedef struct s_wall
{
	float	ca;
	int		line_h;
	float	ty_step;
	float	ty_off;
	int		line_off;
	float	ty;
	float	tx;
}	t_wall;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_mlx;

typedef struct s_vec
{
	int	x;
	int	y;
	int	color;
}	t_vec;

typedef struct s_bres
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error[2];
}	t_bres;

typedef struct s_cubed
{
	struct s_map		map;
	struct s_mlx		mlx;
	struct s_player		player;
	struct s_bres		bres;
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*east;
	mlx_texture_t		*west;
	int					mouse;
}	t_cubed;

void	toggle(t_cubed *cubed);
//MAP_PARSING
char			**get_file_contents(t_cubed *cubed, char *filename);
int				get_map_size(char **file);
char			**get_map(t_cubed *cubed, char **file);
void			map_parsing(t_cubed *cubed, char *filename);
//DRAW
void			draw_map(t_cubed *cubed);
void			draw_background(t_cubed *cubed);
void			draw_rectangle(t_cubed *cubed, int ry, int rx, int color);
void			draw(t_cubed *cubed);
void			draw_player(t_cubed *cubed);
//DRAW_UTIL
void			my_pixel_put(mlx_image_t *image, int x, int y, int color);
void			ray_plotline(t_cubed *cubed, t_vec v1, t_vec v2);
void			plotline(t_cubed *cubed, t_vec v1, t_vec v2);
void			draw_map_outlines(t_cubed *cubed);
//INIT
void			init_mlx(t_cubed *cubed);
//MOVE
void			move_player(t_cubed *cubed, int key);
//MOVE_2
void			rotate_player(t_cubed *cubed, int key);
void			mouse_rotate(t_cubed *cubed);
//UTIL
uint32_t		*get_text_color(mlx_texture_t *texture, t_cubed *cubed);
void			load_text(t_cubed *cubed);
void			check_keys(t_cubed *cubed);
void			mouse_rotate(t_cubed *cubed);
void			check_for_player(t_cubed *cubed, int y, int x);
//UTIL_2
float			deg_to_rad(float a);
float			fix_ang(float a);
void			find_player_position(t_cubed *cubed);
//RAYCAST
mlx_texture_t	*check_what_ray_hit_first(t_cubed *cubed, t_ray *ray);
void			\
calculate_wall_dimensions(t_cubed *cubed, t_ray *ray, t_wall *wall);
void			draw_walls(t_cubed *cubed, t_ray *ray, mlx_texture_t *text);
void			cast_rays2d(t_cubed *cubed);
//CAST_VERTICAL
void			depth_of_field_v(t_cubed *cubed, t_ray *ray);
void			get_ray_position_v(t_cubed *cubed, t_ray *ray);
void			cast_vertical_rays(t_cubed *cubed, t_ray *ray);
//CAST_HORIZONTAL
void			get_ray_position_h(t_cubed *cubed, t_ray *ray);
void			depth_of_field_h(t_cubed *cubed, t_ray *ray);
void			cast_horizontal_rays(t_cubed *cubed, t_ray *ray);
//PARSE_UTIL
int				check_for_empty_row(char *row);
int				iterate_to_newline(char *row);
void			get_player_angle(t_cubed *cubed, char direction);
void			check_index_spot(t_cubed *cubed, char index);
int				check_direction(char index);
//PARSE_UTIL2
int				ft_is_white_space(char c);
int				iterate_over_white_spaces(char *row);
int				get_rgba(int r, int g, int b, int a);
int				get_2d_array_size(char **array);
int				check_if_map_started(char *row);
//PARSE_UTIL3
char			**append_2d(char **twod, char *str_to_add);
void			free_string_array(char **array);
void			error_exit(t_cubed *cubed, char *error_msg);
char			*texture_path(t_cubed *cubed, char *row);
void			free_all(t_cubed *cubed);
//MAP_CHECK
void			check_for_invalid_attributes(t_cubed *cubed, char **map);
void			check_map(t_cubed *cubed, char **map);
void			check_row(t_cubed *cubed, char *row, int *spawn);
int				check_if_walls_connect(char *row, char *next_row);
int				check_wall(char *row, char *next_row, int *wall);
//MAP_CHECK2
int				iterate_to_map_start(char **file);
void			nullify_map(t_cubed *cubed);
int				check_file_name(char *filename);
void			check_if_east_or_west(t_cubed *cubed, char *row);
void			check_top_and_bottom(t_cubed *cubed, char *row);
//GET_INT_MAP
void			convert_map_to_int(t_cubed *cubed, char **map);
void			fill_int_array(t_cubed *cubed, char *row);
void			fill_int(t_cubed *cubed, int *map_index, char map_char);
void			get_int_map_size(t_cubed *cubed, char **map);
//GET_MAP_ATTR
void			get_map_attributes(t_cubed *cubed, char **file);
void			get_attribute(t_cubed *cubed, char *row);
int				get_color(t_cubed *cubed, char *row);
void			get_colors(t_cubed *cubed, char *row);
void			get_textures(t_cubed *cubed, char *row);

#endif
