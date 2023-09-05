/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical_rays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:37:06 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/05 15:01:41 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	depth_of_field_v(t_cubed *cubed, t_ray *ray)
{
	while (ray->dof < cubed->map.map_x) 
	{
		ray->mx = (int)(ray->rx) / cubed->map.map_s;
		ray->my = (int)(ray->ry) / cubed->map.map_s;
		ray->mp = ray->my * cubed->map.map_x + ray->mx;
		if (ray->mp > 0 && ray->mp < cubed->map.map_x
			* cubed->map.map_y && cubed->map.map[ray->mp] == 1)
		{
			ray->dof = cubed->map.map_x;
			ray->dis_v = cos(deg_to_rad(ray->ra)) * (ray->rx - cubed->player.px)
				- sin(deg_to_rad(ray->ra)) * (ray->ry - cubed->player.py);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}

void	get_ray_position_v(t_cubed *cubed, t_ray *ray)
{
	if (cos(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->rx = (((int)cubed->player.px
					/ cubed->map.map_s) * cubed->map.map_s) + cubed->map.map_s;
		ray->ry = (cubed->player.px - ray->rx) * ray->tan + cubed->player.py;
		ray->xo = cubed->map.map_s;
		ray->yo = -ray->xo * ray->tan;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->rx = (((int)cubed->player.px
					/ cubed->map.map_s) * cubed->map.map_s) - 0.0001;
		ray->ry = (cubed->player.px - ray->rx) * ray->tan + cubed->player.py;
		ray->xo = -cubed->map.map_s;
		ray->yo = -ray->xo * ray->tan;
	}
	else
	{
		ray->rx = cubed->player.px;
		ray->ry = cubed->player.py;
		ray->dof = cubed->map.map_x;
	}
}

void	cast_vertical_rays(t_cubed *cubed, t_ray *ray)
{
	ray->dof = 0;
	ray->side = 0;
	ray->dis_v = 100000;
	ray->tan = tan(deg_to_rad(ray->ra));
	get_ray_position_v(cubed, ray);
	depth_of_field_v(cubed, ray);
	ray->vx = ray->rx; 
	ray->vy = ray->ry;
}
