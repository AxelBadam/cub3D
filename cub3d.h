/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/17 17:03:04 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#define PI 3.141592653
#define WIDTH 1024
#define HEIGHT 512
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533

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
} t_map;

typedef struct s_player
{
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
}	t_ray;

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

typedef struct s_cubed
{
	struct s_map map;
	struct s_mlx mlx;
	struct s_player player;
	struct s_bres bres;
}	t_cubed;

char	**append_2d(char **twod, char *str_to_add);
void	free_string_array(char **array);
int		get_2d_array_size(char **array);
void	draw_map(t_cubed *cubed);