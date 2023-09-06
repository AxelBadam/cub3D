/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:32:17 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/06 12:15:53 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_cubed *cubed)
{
	int	x;
	int	y;

	x = 75;
	y = 75;
	while (x < (75 + 4))
	{
		while (y < (75 + 4))
		{
			my_pixel_put(cubed->mlx.image, x, y, 0xFF00FFFF);
			y++;
		}
		y = 75;
		x++;
	}
}

void	draw_map(t_cubed *cubed)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	while (y < cubed->map.map_y)
	{
		while (x < cubed->map.map_x)
		{
			if (cubed->map.map[y * cubed->map.map_x + x] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			draw_rectangle(cubed,
				(y * cubed->map.map_s + cubed->map.map_postion_y)
				- (cubed->player.og_y - 75), (x * cubed->map.map_s
					+ cubed->map.map_postion_x)
				- (cubed->player.og_x - 75), color);
			x++;
		}
		x = 0;
		y++;
	}
	draw_map_outlines(cubed);
}

void	draw_rectangle(t_cubed *cubed, int ry, int rx, int color)
{
	int	x;
	int	y;

	x = 0;
	y = ry;
	while (y < ry + cubed->map.map_s)
	{
		x = rx;
		while (x < rx + cubed->map.map_s)
		{
			if (y > 3 && y < 153 && x > 3 && x < 153)
				my_pixel_put(cubed->mlx.image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_background(t_cubed *cubed)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cubed->mlx.image, x, y, cubed->map.cealing_color);
			else
				mlx_put_pixel(cubed->mlx.image, x, y, cubed->map.floor_color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw(t_cubed *cubed)
{
	if (cubed->mlx.image)
	{
		mlx_delete_image(cubed->mlx.mlx, cubed->mlx.image);
		cubed->mlx.image = NULL;
	}
	cubed->mlx.image = mlx_new_image(cubed->mlx.mlx, WIDTH, HEIGHT);
	draw_background(cubed);
	cast_rays2d(cubed);
	draw_map(cubed);
	draw_player(cubed);
	if (mlx_image_to_window(cubed->mlx.mlx, cubed->mlx.image, 0, 0) == -1)
	{
		mlx_close_window(cubed->mlx.mlx);
		puts(mlx_strerror(mlx_errno));
		exit(69);
	}
}
