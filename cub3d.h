/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/28 17:38:12 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>

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
}			t_player;

typedef struct s_cubed
{
	void	*mlx;
	void 	*win;
	//t_mouse *mouse;
	mlx_image_t *img;
	t_menu *menu;
	t_player *player;
}			t_cubed;

typedef struct s_mouse
{
	char				is_pressed;
	int					x;
	int					y;
	int					previous_x;
	int					previous_y;
}						t_mouse;