/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:35 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/06 11:58:26 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_outlines(t_cubed *cubed)
{
	plotline(cubed, (t_vec){3, 3, cubed->map.cealing_color - 2000},
		(t_vec){3, 153, cubed->map.cealing_color - 2000});
	plotline(cubed, (t_vec){3, 153, cubed->map.cealing_color - 2000},
		(t_vec){153, 153, cubed->map.cealing_color - 2000});
	plotline(cubed, (t_vec){153, 153, cubed->map.cealing_color - 2000},
		(t_vec){153, 3, cubed->map.cealing_color - 2000});
	plotline(cubed, (t_vec){153, 3, cubed->map.cealing_color - 2000},
		(t_vec){3, 3, cubed->map.cealing_color - 2000});
}

void	my_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (y < HEIGHT && y >= 0 && x < WIDTH && x >= 0)
		mlx_put_pixel(image, x, y, color);
}

void	plotline(t_cubed *cubed, t_vec v1, t_vec v2)
{
	cubed->bres.dx = abs(v2.x - v1.x);
	cubed->bres.dy = -abs(v2.y - v1.y);
	cubed->bres.sx = -1;
	if (v1.x < v2.x)
		cubed->bres.sx = 1;
	cubed->bres.sy = -1;
	if (v1.y < v2.y)
		cubed->bres.sy = 1;
	cubed->bres.error[0] = cubed->bres.dx + cubed->bres.dy;
	while (v1.x != v2.x || v1.y != v2.y)
	{
		my_pixel_put(cubed->mlx.image, v1.x, v1.y, v1.color);
		cubed->bres.error[1] = 2 * cubed->bres.error[0];
		if (cubed->bres.error[1] >= cubed->bres.dy)
		{
			cubed->bres.error[0] += cubed->bres.dy;
			v1.x += cubed->bres.sx;
		}
		if (cubed->bres.error[1] <= cubed->bres.dx)
		{
			cubed->bres.error[0] += cubed->bres.dx;
			v1.y += cubed->bres.sy;
		}
	}
	my_pixel_put(cubed->mlx.image, v1.x, v1.y, v1.color);
}

void	ray_plotline(t_cubed *cubed, t_vec v1, t_vec v2)
{
	cubed->bres.dx = abs(v2.x - v1.x);
	cubed->bres.dy = -abs(v2.y - v1.y);
	cubed->bres.sx = -1;
	if (v1.x < v2.x)
		cubed->bres.sx = 1;
	cubed->bres.sy = -1;
	if (v1.y < v2.y)
		cubed->bres.sy = 1;
	cubed->bres.error[0] = cubed->bres.dx + cubed->bres.dy;
	while (v1.x != v2.x || v1.y != v2.y)
	{
		if (v1.x > 3 && v1.x < 153 && v1.y > 3 && v1.y < 154)
			my_pixel_put(cubed->mlx.image, v1.x, v1.y, v1.color);
		cubed->bres.error[1] = 2 * cubed->bres.error[0];
		if (cubed->bres.error[1] >= cubed->bres.dy)
		{
			cubed->bres.error[0] += cubed->bres.dy;
			v1.x += cubed->bres.sx;
		}
		if (cubed->bres.error[1] <= cubed->bres.dx)
		{
			cubed->bres.error[0] += cubed->bres.dx;
			v1.y += cubed->bres.sy;
		}
	}
}
