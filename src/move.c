/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:23 by atuliara          #+#    #+#             */
/*   Updated: 2023/08/31 14:53:14 by ekoljone         ###   ########.fr       */
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

void 	backward(t_cubed *cubed, int yo, int xo)
{
	int ipx;
	int ipy;
	int ipx_sub_xo;
	int ipy_sub_yo;
	
	ipx = cubed->player.px / (float)cubed->map.mapS;
	ipy = cubed->player.py / (float)cubed->map.mapS;
	ipx_sub_xo = (cubed->player.px-xo) / (float)cubed->map.mapS;
	ipy_sub_yo = (cubed->player.py-yo) / (float)cubed->map.mapS;
	printf("ipx = %f\nipy = %f\nipx_sub_xo = %f\nipy_sub_yo = %f\n", cubed->player.px / cubed->map.mapS, cubed->player.py / cubed->map.mapS, (cubed->player.px-xo) / cubed->map.mapS,
	(cubed->player.py-yo) / cubed->map.mapS);
	printf("if(cubed->map.map[%d] == 0)\n{\ncubed->player.px -= cubed->player.dx * (cubed->map.mapS / 4);\ncubed->map.map_postionX += cubed->player.dx * (cubed->map.mapS / 4);\n}\nif(cubed->map.map[%d] == 0)\n{\ncubed->player.py -= cubed->player.dy * (cubed->map.mapS / 4);\ncubed->map.map_postionY +=cubed->player.dy * (cubed->map.mapS / 4);\n}\n", ipy * cubed->map.mapX + ipx_sub_xo, ipy_sub_yo * cubed->map.mapX + ipx);
	printf("MAPSIZE = %i\n", cubed->map.mapS);
	if(cubed->map.map[ipy * cubed->map.mapX + ipx_sub_xo] == 0)
	{
		cubed->player.px -= cubed->player.dx * 2;
		cubed->map.map_postionX += cubed->player.dx * 2;
	}
  	if(cubed->map.map[ipy_sub_yo * cubed->map.mapX + ipx] == 0)
	{
		cubed->player.py -= cubed->player.dy * 2;
		cubed->map.map_postionY +=cubed->player.dy * 2;
	}
}

void	forward(t_cubed *cubed, int xo, int yo)
{
	int ipy;
	int ipx;
	int ipx_add_xo;
	int ipy_add_yo;

	ipx = cubed->player.px / (float)cubed->map.mapS;
	ipy = cubed->player.py / (float)cubed->map.mapS;
	ipx_add_xo = (cubed->player.px + xo) / (float)cubed->map.mapS;
	ipy_add_yo = (cubed->player.py + yo) / (float)cubed->map.mapS;

	if(cubed->map.map[ipy * cubed->map.mapX + ipx_add_xo] == 0)
	{
		cubed->player.px += cubed->player.dx * (cubed->map.mapS / 4);
		cubed->map.map_postionX -= cubed->player.dx * (cubed->map.mapS / 4);
	}
	if(cubed->map.map[ipy_add_yo * cubed->map.mapX + ipx] == 0)
	{
		cubed->player.py += cubed->player.dy * (cubed->map.mapS / 4);
		cubed->map.map_postionY -= cubed->player.dy * (cubed->map.mapS / 4);
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
    if (cubed->map.map[new_ipy * cubed->map.mapX + new_ipx] == 0)
    {
        cubed->player.px += perpend_dx * (cubed->map.mapS / 4);
        cubed->map.map_postionX -= perpend_dx * (cubed->map.mapS / 4);
        cubed->player.py += perpend_dy * (cubed->map.mapS / 4);
        cubed->map.map_postionY -= perpend_dy * (cubed->map.mapS / 4);
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
    if (cubed->map.map[new_ipy * cubed->map.mapX + new_ipx] == 0)
    {
    	cubed->player.px += perpend_dx * (cubed->map.mapS / 4);
        cubed->map.map_postionX -= perpend_dx * (cubed->map.mapS / 4);
    	cubed->player.py += perpend_dy * (cubed->map.mapS / 4);
    	cubed->map.map_postionY -= perpend_dy * (cubed->map.mapS / 4);
    }
}

void	move_player(t_cubed *cubed, int key)
{
	int xo; 
	int yo; 
	
	xo = 0;
	yo = 0;
	if(cubed->player.dx < 0)
		xo = -20;
	else
		xo = 20;
	if (cubed->player.dy < 0)
		yo = -20;
	else
		yo = 20;
	if (key == 'W')
		forward(cubed, xo, yo);
	else if (key == 'S')
		backward(cubed, xo, yo);
	else if (key == 'D')
		to_right(cubed);
	else if (key == 'A')
		to_left(cubed);	
}

