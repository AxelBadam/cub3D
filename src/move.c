/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:47:23 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/14 11:55:09 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	backward(t_cubed *cubed)
{
	int	ipx;
	int	ipy;
	int	new_ipx;
	int	new_ipy;

	ipx = cubed->player.px / (float)cubed->map.map_s;
	ipy = cubed->player.py / (float)cubed->map.map_s;
	new_ipx = (cubed->player.px - cubed->player.dx * 10)
		/ (float)cubed->map.map_s;
	new_ipy = (cubed->player.py - cubed->player.dy * 10)
		/ (float)cubed->map.map_s;
	if (cubed->map.map[ipy * cubed->map.map_x + new_ipx] == 0)
	{
		cubed->player.px -= cubed->player.dx * 2;
		cubed->map.map_postion_x += cubed->player.dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.map_x + ipx] == 0)
	{
		cubed->player.py -= cubed->player.dy * 2;
		cubed->map.map_postion_y += cubed->player.dy * 2;
	}
}

static void	forward(t_cubed *cubed)
{
	int	ipy;
	int	ipx;
	int	new_ipx;
	int	new_ipy;

	ipx = cubed->player.px / (float)cubed->map.map_s;
	ipy = cubed->player.py / (float)cubed->map.map_s;
	new_ipx = (cubed->player.px + cubed->player.dx * 10)
		/ (float)cubed->map.map_s;
	new_ipy = (cubed->player.py + cubed->player.dy * 10)
		/ (float)cubed->map.map_s;
	if (cubed->map.map[ipy * cubed->map.map_x + new_ipx] == 0)
	{
		cubed->player.px += cubed->player.dx * 2;
		cubed->map.map_postion_x -= cubed->player.dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.map_x + ipx] == 0)
	{
		cubed->player.py += cubed->player.dy * 2;
		cubed->map.map_postion_y -= cubed->player.dy * 2;
	}
}

static void	to_left(t_cubed *cubed)
{
	float	perpend_dx;
	float	perpend_dy;
	int		new_ipx;
	int		new_ipy;

	perpend_dx = cubed->player.dy;
	perpend_dy = -cubed->player.dx;
	new_ipx = (cubed->player.px + perpend_dx * 10) / cubed->map.map_s;
	new_ipy = (cubed->player.py + perpend_dy * 10) / cubed->map.map_s;
	if (cubed->map.map[((int)cubed->player.py / cubed->map.map_s)
			* cubed->map.map_x + new_ipx] == 0)
	{
		cubed->player.px += perpend_dx * 2;
		cubed->map.map_postion_x -= perpend_dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.map_x + 
			(int)cubed->player.px / cubed->map.map_s] == 0)
	{
		cubed->player.py += perpend_dy * 2;
		cubed->map.map_postion_y -= perpend_dy * 2;
	}
}

static void	to_right(t_cubed *cubed)
{
	float	perpend_dx;
	float	perpend_dy;
	int		new_ipx;
	int		new_ipy;

	perpend_dx = -cubed->player.dy;
	perpend_dy = cubed->player.dx;
	new_ipx = (cubed->player.px + perpend_dx * 10) / cubed->map.map_s;
	new_ipy = (cubed->player.py + perpend_dy * 10) / cubed->map.map_s;
	if (cubed->map.map[((int)cubed->player.py / cubed->map.map_s)
			* cubed->map.map_x + new_ipx] == 0)
	{
		cubed->player.px += perpend_dx * 2;
		cubed->map.map_postion_x -= perpend_dx * 2;
	}
	if (cubed->map.map[new_ipy * cubed->map.map_x 
			+ (int)cubed->player.px / cubed->map.map_s] == 0)
	{
		cubed->player.py += perpend_dy * 2;
		cubed->map.map_postion_y -= perpend_dy * 2;
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
