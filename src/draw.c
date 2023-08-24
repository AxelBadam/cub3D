/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:32:17 by atuliara          #+#    #+#             */
/*   Updated: 2023/08/24 17:05:25 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_cubed *cubed)
{
	int	x;
	int	y;

	x = 75;
	y = 75;
	while(x < (75 + 4))
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
	int	i = 0;
	int	x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;
	int color;
	while (y < cubed->map.mapY)
	{
		while (x < cubed->map.mapX)
		{
			if (cubed->map.map[y * cubed->map.mapX + x] == 1)
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			xo = x * cubed->map.mapS + cubed->map.map_postionX;
			yo = y * cubed->map.mapS + cubed->map.map_postionY;
			draw_rectangle(cubed, yo - (cubed->player.og_y - 75), xo - (cubed->player.og_x - 75), color);
			x++;
			i++;
		}
		x = 0;
		y++;
	}
	plotline(cubed, (t_vec){3, 3, 0, cubed->map.cealing_color - 2000}, (t_vec){3, 153, 0, cubed->map.cealing_color - 2000});
	plotline(cubed, (t_vec){3, 153, 0, cubed->map.cealing_color - 2000}, (t_vec){153, 153, 0, cubed->map.cealing_color - 2000});
	plotline(cubed, (t_vec){153, 153, 0, cubed->map.cealing_color - 2000}, (t_vec){153, 3, 0, cubed->map.cealing_color - 2000});
	plotline(cubed, (t_vec){153, 3, 0, cubed->map.cealing_color - 2000}, (t_vec){3, 3, 0, cubed->map.cealing_color - 2000});
}

void	draw_rectangle(t_cubed *cubed, int ry, int rx, int color)
{
	int	x = 0;
	int y = ry;

	while (y < ry + cubed->map.mapS)
	{
		x = rx;
		while (x < rx + cubed->map.mapS)
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
				mlx_put_pixel(cubed->mlx.image, x, y, cubed->map.floor_color);
			else
				mlx_put_pixel(cubed->mlx.image, x, y, cubed->map.cealing_color);
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
	cast_rays2D(cubed);
	draw_map(cubed);
	draw_player(cubed);
	if (mlx_image_to_window(cubed->mlx.mlx, cubed->mlx.image, 0, 0) == -1)
	{
		mlx_close_window(cubed->mlx.mlx);
		puts(mlx_strerror(mlx_errno));
		exit(69);
	}
}

