/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical_rays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:37:06 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/05 11:33:51 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	depth_of_field_v(t_cubed *cubed, t_ray *ray)
{
	while (ray->dof < cubed->map.mapX) 
	{
		ray->mx = (int)(ray->rx) / cubed->map.mapS;
		ray->my = (int)(ray->ry) / cubed->map.mapS;
		ray->mp = ray->my * cubed->map.mapX + ray->mx;
		if (ray->mp > 0 && ray->mp < cubed->map.mapX
			* cubed->map.mapY && cubed->map.map[ray->mp] == 1)
		{
			ray->dof = cubed->map.mapX;
			ray->disV = cos(deg_to_rad(ray->ra)) * (ray->rx - cubed->player.px)
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
					/ cubed->map.mapS) * cubed->map.mapS) + cubed->map.mapS;
		ray->ry = (cubed->player.px - ray->rx) * ray->Tan + cubed->player.py;
		ray->xo = cubed->map.mapS;
		ray->yo = -ray->xo * ray->Tan;
	}
	else if (cos(deg_to_rad(ray->ra)) < -0.001)
	{
		ray->rx = (((int)cubed->player.px
					/ cubed->map.mapS) * cubed->map.mapS) - 0.0001;
		ray->ry = (cubed->player.px - ray->rx) * ray->Tan + cubed->player.py;
		ray->xo = -cubed->map.mapS;
		ray->yo = -ray->xo * ray->Tan;
	}
	else
	{
		ray->rx = cubed->player.px;
		ray->ry = cubed->player.py;
		ray->dof = cubed->map.mapX;
	}
}

void	cast_vertical_rays(t_cubed *cubed, t_ray *ray)
{
	ray->dof = 0;
	ray->side = 0;
	ray->disV = 100000;
	ray->Tan = tan(deg_to_rad(ray->ra));
	get_ray_position_v(cubed, ray);
	depth_of_field_v(cubed, ray);
	ray->vx = ray->rx; 
	ray->vy = ray->ry;
}
