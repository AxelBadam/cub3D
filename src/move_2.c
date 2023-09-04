/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:51:29 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/04 17:08:34 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_cubed *cubed, int key)
{
	if (key == MLX_KEY_RIGHT)
		cubed->player.pa -= 5;
	else
		cubed->player.pa += 5;
	cubed->player.pa = fix_ang(cubed->player.pa);
	cubed->player.dx = cos(deg_to_rad(cubed->player.pa));
	cubed->player.dy = -sin(deg_to_rad(cubed->player.pa));
}

void	mouse_rotate(t_cubed *cubed)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cubed->mlx.mlx, &x, &y);
	x -= WIDTH / 2;
	cubed->player.pa += (float)x / 40;
	cubed->player.pa = fix_ang(cubed->player.pa);
	mlx_set_mouse_pos(cubed->mlx.mlx, WIDTH / 2, HEIGHT / 2);
	cubed->player.dx = cos(deg_to_rad(cubed->player.pa));
	cubed->player.dy = -sin(deg_to_rad(cubed->player.pa));
}