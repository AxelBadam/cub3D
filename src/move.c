/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:23 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/01 16:23:50 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_cubed *cubed, int key)
{
	if (key == MLX_KEY_RIGHT)
		cubed->player.pa -= 5;
	else
		cubed->player.pa += 5;
	cubed->player.pa = FixAng(cubed->player.pa);
	cubed->player.dx = cos(degToRad(cubed->player.pa));
	cubed->player.dy = -sin(degToRad(cubed->player.pa));
}

void 	backward(t_cubed *cubed)
{
	int ipx;
	int ipy;
	int new_ipx;
	int new_ipy;

	ipx = cubed->player.px / (float)cubed->map.mapS;
	ipy = cubed->player.py / (float)cubed->map.mapS;
	new_ipx = (cubed->player.px - cubed->player.dx * 10) / (float)cubed->map.mapS;
	new_ipy = (cubed->player.py - cubed->player.dy * 10) / (float)cubed->map.mapS;
	if (cubed->map.map[ipy * cubed->map.mapX + new_ipx] == 0)
	{
		cubed->player.px -= cubed->player.dx * 2;
		cubed->map.map_postionX += cubed->player.dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.mapX + ipx] == 0)
	{
		cubed->player.py -= cubed->player.dy * 2;
		cubed->map.map_postionY += cubed->player.dy * 2;
	}
}

void	forward(t_cubed *cubed)
{
	int ipy;
	int ipx;
	int new_ipx;
	int new_ipy;

	ipx = cubed->player.px / (float)cubed->map.mapS;
	ipy = cubed->player.py / (float)cubed->map.mapS;
	new_ipx = (cubed->player.px + cubed->player.dx * 10) / (float)cubed->map.mapS;
	new_ipy = (cubed->player.py + cubed->player.dy * 10) / (float)cubed->map.mapS;
	if (cubed->map.map[ipy * cubed->map.mapX + new_ipx] == 0)
	{
		cubed->player.px += cubed->player.dx * 2;
		cubed->map.map_postionX -= cubed->player.dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.mapX + ipx] == 0)
	{
		cubed->player.py += cubed->player.dy * 2;
		cubed->map.map_postionY -= cubed->player.dy * 2;
	}
}

void	to_left(t_cubed *cubed)
{	
	float perpend_dx;
	float perpend_dy;
	int new_ipx;
	int new_ipy;
	
    perpend_dx = cubed->player.dy;
    perpend_dy = -cubed->player.dx;
	new_ipx = (cubed->player.px + perpend_dx * 10) / cubed->map.mapS;
    new_ipy= (cubed->player.py + perpend_dy * 10) / cubed->map.mapS;
	if (cubed->map.map[((int)cubed->player.py / cubed->map.mapS) * cubed->map.mapX + new_ipx] == 0)
	{
		cubed->player.px += perpend_dx * 2;
        cubed->map.map_postionX -= perpend_dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.mapX + (int)cubed->player.px / cubed->map.mapS] == 0)
	{
		cubed->player.py += perpend_dy * 2;
    	cubed->map.map_postionY -= perpend_dy * 2;
	}
 }	

void	to_right(t_cubed *cubed)
{
	float perpend_dx;
	float perpend_dy;
	int new_ipx;
	int new_ipy;
	
    perpend_dx = -cubed->player.dy;
    perpend_dy = cubed->player.dx;
    new_ipx = (cubed->player.px + perpend_dx * 10) / cubed->map.mapS;
    new_ipy = (cubed->player.py + perpend_dy * 10) / cubed->map.mapS;
	if (cubed->map.map[((int)cubed->player.py / cubed->map.mapS) * cubed->map.mapX + new_ipx] == 0)
	{
		cubed->player.px += perpend_dx * 2;
        cubed->map.map_postionX -= perpend_dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.mapX + (int)cubed->player.px / cubed->map.mapS] == 0)
	{
		cubed->player.py += perpend_dy * 2;
    	cubed->map.map_postionY -= perpend_dy * 2;
	}
}

void	move_player(t_cubed *cubed, int key)
{
	if (key == 'W')
		forward(cubed);
	else if (key == 'S')
		backward(cubed);
	else if (key == 'D')
		to_right(cubed);
	else if (key == 'A')
		to_left(cubed);	
}

