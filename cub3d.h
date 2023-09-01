/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/01 15:03:40 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define COL_OFF 20
#define WIDTH 1440
#define HEIGHT 960

typedef struct s_map
{
	int			mapS;
	int			mapX;
	int			mapY;
	int			*map;
	char		*path_to_north;
	char		*path_to_south;
	char		*path_to_west;
	char		*path_to_east;
	long int	floor_color;
	long int	cealing_color;
	float		map_postionX;
	float		map_postionY;
} t_map;

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
	float	disV;
	float	disH;
	float	Tan;
	float	len;
	float	flag;
}	t_ray;

typedef struct s_wall
{
	float	ca;
	int		lineH;
	float	ty_step;
	float	ty_off;
	int		lineOff;
	float	ty;
	float	tx;
}	t_wall;

typedef struct s_mlx
{
	mlx_t	*mlx;
	mlx_image_t	*image;
}	t_mlx;

typedef struct s_vec
{
	int	x;
	int	y;
	int	z;
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

typedef struct s_keyflag
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}				t_keyflag;

typedef struct s_cubed
{
	struct s_map map;
	struct s_mlx mlx;
	struct s_player player;
	struct s_bres bres;
	struct s_keyflag key;
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *east;
	mlx_texture_t *west;
}	t_cubed;

//PARS
char		**append_2d(char **twod, char *str_to_add);
void		free_string_array(char **array);
int			get_2d_array_size(char **array);
void		map_parsing(t_cubed *cubed, char *filename);
//DRAW
void		draw_map(t_cubed *cubed);
void		draw_background(t_cubed *cubed);
void		draw_rectangle(t_cubed *cubed, int ry, int rx, int color);
void		draw(t_cubed *cubed);
void		draw_player(t_cubed *cubed);
// DRAW_UTIL
void		my_pixel_put(mlx_image_t *image, int x, int y, int color);
void		ray_plotline(t_cubed *cubed, t_vec v1, t_vec v2);
void		plotline(t_cubed *cubed, t_vec v1, t_vec v2);
//RC UTIL
float degToRad(float a);
float distance(int ax, int ay, int bx, int by, float ang);
float FixAng(float a);

//INIT
void	init_mlx(t_cubed *cubed);
//MOVE
void		move_player(t_cubed *cubed, int key);
void		rotate_player(t_cubed *cubed, int key);

//UTIL
void 		load_text(t_cubed *cubed);
void		check_keys(t_cubed *cubed);
uint32_t	*get_text_color(mlx_texture_t *texture);
void		find_player_position(t_cubed *cubed);
//RAYCAST
mlx_texture_t	*check_what_ray_hit_first(t_cubed *cubed, t_ray *ray);
void	calculate_wall_dimensions(t_cubed *cubed, t_ray *ray, t_wall *wall);
void	draw_walls(t_cubed *cubed, t_ray *ray, mlx_texture_t *text);
void	cast_rays2D(t_cubed *cubed);
//CAST_VERTICAL
void	depth_of_field_V(t_cubed *cubed, t_ray *ray);
void	get_ray_position_V(t_cubed *cubed, t_ray *ray);
void	cast_vertical_rays(t_cubed *cubed, t_ray *ray);
//CAST_HORIZONTAL
void	get_ray_position_H(t_cubed *cubed, t_ray *ray);
void	depth_of_field_H(t_cubed *cubed, t_ray *ray);
void	cast_horizontal_rays(t_cubed *cubed, t_ray *ray);
