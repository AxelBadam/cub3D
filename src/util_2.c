/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:53:24 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/06 12:00:06 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

float	fix_ang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

void	find_player_position(t_cubed *cubed)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cubed->map.map_y)
	{
		while (x < cubed->map.map_x)
		{
			check_for_player(cubed, y, x);
			x++;
		}
		x = 0;
		y++;
	}
}
