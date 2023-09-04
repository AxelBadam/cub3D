/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/04 14:52:36 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(void *param)
{
	t_cubed	*cubed;

	cubed = param;
	check_keys(cubed);
	mouse_rotate(cubed);
	draw(cubed);
}

void	cub3d(t_cubed *cubed)
{
	cubed->map.mapS = 24;
	find_player_position(cubed);
	cubed->player.dx = cos(degToRad(cubed->player.pa));
	cubed->player.dy = -sin(degToRad(cubed->player.pa));
	init_mlx(cubed);
	load_text(cubed);
	draw(cubed);
	mlx_loop_hook(cubed->mlx.mlx, &update, cubed);
	//mlx_mouse_hook(cubed->mlx.mlx, &mouse_rotate, cubed);
	mlx_loop(cubed->mlx.mlx);
	mlx_terminate(cubed->mlx.mlx);
}

int main(int argc, char **argv)
{
	t_cubed	cubed;

	if (argc != 2)
		return (1);
	map_parsing(&cubed, argv[1]);
	cub3d(&cubed);
	return (0);
}
