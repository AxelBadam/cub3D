/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/03 16:43:15 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <math.h>

typedef struct s_menu
{
	mlx_image_t *img;
}			t_menu;


typedef struct s_player
{
	int x;
	int y;
	int color;
	int start_x;
	int start_y;
	int pdx;
	int pdy;
	int pa;
}			t_player;

typedef struct s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct s_map
{
	int		x;
	int		y;
	int		size;
	int		*map;
	int 	color;
}						t_map;

typedef struct s_rect
{
    int	x;
    int	y;
    int width;
    int height;
    int color;
}	t_rect;

typedef struct s_cubed
{
	void		*mlx;
	void 		*win;
	//t_mouse 	*mouse;
	mlx_image_t *map_img;	
	mlx_image_t *img;
	t_menu 		*menu;
	t_player 	*player;
	t_map		*map;
	t_rect		*rect;
	int			changes;
}			t_cubed;

typedef struct s_mouse
{
	char				is_pressed;
	int					x;
	int					y;
	int					previous_x;
	int					previous_y;
}						t_mouse;