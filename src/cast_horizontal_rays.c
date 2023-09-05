/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal_rays.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:35:27 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/05 12:17:18 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_position_h(t_cubed *cubed, t_ray *ray)
{
	if (sin(deg_to_rad(ray->ra)) > 0.001)
	{
		ray->ry = (((int)cubed->player.py
					/ cubed->map.mapS) * cubed->map.mapS) - 0.0001;
		ray->rx = (cubed->player.py - ray->ry) * ray->Tan + cubed->player.px;
		ray->yo = -cubed->map.mapS;
		ray->xo = -ray->yo * ray->Tan;
	}
	else if (sin(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->ry = (((int)cubed->player.py / cubed->map.mapS)
				* cubed->map.mapS) + cubed->map.mapS;
		ray->rx = (cubed->player.py - ray->ry) * ray->Tan + cubed->player.px;
		ray->yo = cubed->map.mapS;
		ray->xo = -ray->yo * ray->Tan;
	}
	else
	{
		ray->rx = cubed->player.px;
		ray->ry = cubed->player.py;
		ray->dof = cubed->map.mapY;
	}
}

void	depth_of_field_h(t_cubed *cubed, t_ray *ray)
{
	while (ray->dof < cubed->map.mapY) 
	{
		ray->mx = (int)(ray->rx) / cubed->map.mapS;
		ray->my = (int)(ray->ry) / cubed->map.mapS;
		ray->mp = ray->my * cubed->map.mapX + ray->mx;
		if (ray->mp > 0 && ray->mp < cubed->map.mapX
			* cubed->map.mapY && cubed->map.map[ray->mp] == 1)
		{
			ray->dof = cubed->map.mapY;
			ray->disH = cos(deg_to_rad(ray->ra))
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
	ray->disH = 100000;
	ray->Tan = 1.0 / ray->Tan; 
	get_ray_position_h(cubed, ray);
	depth_of_field_h(cubed, ray);
}
