/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:40:11 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/13 10:51:00 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*check_what_ray_hit_first(t_cubed *cubed, t_ray *ray)
{
	mlx_texture_t	*text;

	ray->flag_h = 1;
	text = NULL;
	if (ray->dis_v >= ray->dis_h)
	{
		if (ray->ra < 360 && ray->ra > 180)
			text = cubed->south;
		else if (ray->ra > 0 && ray->ra < 180)
			text = cubed->north;
	}
	if (!text && ray->dis_v <= ray->dis_h)
	{
		ray->flag_h = 0;
		ray->rx = ray->vx; 
		ray->ry = ray->vy; 
		ray->dis_h = ray->dis_v;
		if (ray->ra < 270 && ray->ra > 90)
			text = cubed->west;
		else if (ray->ra > 270 || ray->ra < 90)
			text = cubed->east;
	}
	return (text);
}

void	calculate_wall_dimensions(t_cubed *cubed, t_ray *ray, t_wall *wall)
{
	wall->ca = fix_ang(cubed->player.pa - ray->ra);
	ray->dis_h = ray->dis_h * cos(deg_to_rad(wall->ca));
	wall->line_h = (cubed->map.map_s * HEIGHT) / (ray->dis_h);
	wall->ty_step = 32 / (float)wall->line_h;
	wall->ty_off = 0;
	if (wall->line_h > HEIGHT)
	{
		wall->ty_off = (wall->line_h - HEIGHT) / 2;
		wall->line_h = HEIGHT;
	}
	wall->line_off = HEIGHT / 2 - (wall->line_h / 2);
	wall->ty = wall->ty_off * wall->ty_step;
	if (ray->flag_h == 1)
	{
		wall->tx = (int)(ray->rx) % 32;
		if (ray->ra > 180)
			wall->tx = 31 - wall->tx;
	}
	else
	{
		wall->tx = (int)(ray->ry) % 32;
		if ((ray->ra > 90 && ray->ra < 270))
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
	col = get_text_color(text, cubed);
	pixel = (int)wall.ty * 32 + (int)wall.tx;
	while (y < wall.line_h)
	{
		x = 0;
		while (x < 3)
		{
			pixel = (int)wall.ty * 32 + (int)wall.tx;
			my_pixel_put(cubed->mlx.image, ray->r
				* 3 + x, y + wall.line_off, col[pixel]);
			x++;
		}
		wall.ty += wall.ty_step;
		y++;
	}
	free(col);
}

void	cast_rays2d(t_cubed *cubed)
{
	t_ray			ray;
	mlx_texture_t	*text;

	ray.ra = fix_ang(cubed->player.pa + 30);
	ray.r = -1;
	while (++ray.r < 480)
	{
		cast_vertical_rays(cubed, &ray);
		cast_horizontal_rays(cubed, &ray);
		text = check_what_ray_hit_first(cubed, &ray);
		draw_walls(cubed, &ray, text);
		ray.ra = fix_ang(ray.ra - 0.125);
	}
}
