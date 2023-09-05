/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal_rays.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:35:27 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/05 16:49:47 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_position_h(t_cubed *cubed, t_ray *ray)
{
	if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->ry = (((int)cubed->player.py
					/ cubed->map.map_s) * cubed->map.map_s) - 0.0001;
		ray->rx = (cubed->player.py - ray->ry) * ray->tan + cubed->player.px;
		ray->yo = -cubed->map.map_s;
		ray->xo = -ray->yo * ray->tan;
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->ry = (((int)cubed->player.py / cubed->map.map_s)
				* cubed->map.map_s) + cubed->map.map_s;
		ray->rx = (cubed->player.py - ray->ry) * ray->tan + cubed->player.px;
		ray->yo = cubed->map.map_s;
		ray->xo = -ray->yo * ray->tan;
	}
	else
	{
		ray->rx = cubed->player.px;
		ray->ry = cubed->player.py;
		ray->dof = cubed->map.map_y;
	}
}

void	depth_of_field_h(t_cubed *cubed, t_ray *ray)
{
	while (ray->dof < cubed->map.map_y) 
	{
		ray->mx = (int)(ray->rx) / cubed->map.map_s;
		ray->my = (int)(ray->ry) / cubed->map.map_s;
		ray->mp = ray->my * cubed->map.map_x + ray->mx;
		if (ray->mp > 0 && ray->mp < cubed->map.map_x
			* cubed->map.map_y && cubed->map.map[ray->mp] == 1)
		{
			ray->dof = cubed->map.map_y;
			ray->dis_h = cos(deg_to_rad(ray->ra))
				* (ray->rx - cubed->player.px)
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

void	cast_horizontal_rays(t_cubed *cubed, t_ray *ray)
{
	ray->dof = 0;
	ray->dis_h = 100000;
	ray->tan = 1.0 / ray->tan; 
	get_ray_position_h(cubed, ray);
	depth_of_field_h(cubed, ray);
}
