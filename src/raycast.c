/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:40:11 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/01 13:58:41 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*check_what_ray_hit_first(t_cubed *cubed, t_ray *ray)
{
	ray->flag = 1;
	mlx_texture_t *text = NULL;
	if (ray->disV >= ray->disH)
	{
		if (ray->ra < 360 && ray->ra > 180)
			text = cubed->south;
		else if (ray->ra > 0 && ray->ra < 180)
			text = cubed->north;
	}
	if(!text && ray->disV <= ray->disH)
	{ 
		ray->flag = 0.5;
		ray->rx = ray->vx; 
		ray->ry = ray->vy; 
		ray->disH = ray->disV;
		if (ray->ra < 270 && ray->ra > 90)
			text = cubed->west;
		else if (ray->ra > 270 || ray->ra < 90)
			text = cubed->east;
	}
	return (text);
}

void	calculate_wall_dimensions(t_cubed *cubed, t_ray *ray, t_wall *wall)
{
	wall->ca = FixAng(cubed->player.pa - ray->ra);
    ray->disH = ray->disH * cos(degToRad(wall->ca));
   	wall->lineH = (cubed->map.mapS * HEIGHT) / (ray->disH);
   	wall->ty_step = 32/(float)wall->lineH;
    wall->ty_off = 0;
    if (wall->lineH > HEIGHT)
    {
        wall->ty_off = (wall->lineH - HEIGHT) /  2;
        wall->lineH = HEIGHT;
    }
    wall->lineOff = HEIGHT / 2 - (wall->lineH / 2);
    wall->ty = wall->ty_off * wall->ty_step;
	if (ray->flag == 1)
	{
		wall->tx = (int)(ray->rx/2.0) % 32;
		if (ray->ra > 180)
			wall->tx = 31 - wall->tx;
	}
	else
	{
		wall->tx = (int)(ray->ry/2.0) % 32;
		if ( (ray->ra > 90 && ray->ra < 270))
			wall->tx = 31 - wall->tx;
	}
}

void	draw_walls(t_cubed *cubed, t_ray *ray, mlx_texture_t *text)
{
	t_wall		wall;
	int			y;
	int			x;
	u_int32_t	*col;
	int			pixel;

	y = 0;
	calculate_wall_dimensions(cubed, ray, &wall);
	col = get_text_color(text);
	pixel = (int)wall.ty * 32 + (int)wall.tx;
	while (y < wall.lineH)
	{
		x = 0;
		while (x < 3)
		{
			pixel = (int)wall.ty * 32 + (int)wall.tx;	
			my_pixel_put(cubed->mlx.image, ray->r * 3 + x, y + wall.lineOff, col[pixel]);
			x++;
		}
		wall.ty += wall.ty_step;
		y++;
	}
}

void	cast_rays2D(t_cubed *cubed)
{
	t_ray			ray;
	mlx_texture_t	*text;

	ray.ra = FixAng(cubed->player.pa + 30);
	ray.r = -1;
	while (++ray.r < 480)
	{
		cast_vertical_rays(cubed, &ray);
		cast_horizontal_rays(cubed, &ray);
		text = check_what_ray_hit_first(cubed, &ray);
		//float	dist_traveledX = cubed->player.px - cubed->player.og_x;
		//float	dist_traveledY = cubed->player.py - cubed->player.og_y;
		//ray.rx = (ray.rx - dist_traveledX) - (cubed->player.og_x - (float)75);
		//ray.ry = (ray.ry - dist_traveledY) - (cubed->player.og_y - (float)75);
		//ray_plotline(cubed, (t_vec){(cubed->player.px + 3 - dist_traveledX) - (cubed->player.og_x - 75), (cubed->player.py + 3 - dist_traveledY) - (cubed->player.og_y - 75), 0, 0xFF0000FF}, (t_vec){ray.rx, ray.ry, 0, 0xFF0000FF});
		draw_walls(cubed, &ray, text);
		ray.ra = FixAng(ray.ra - 0.125);
	}
}
