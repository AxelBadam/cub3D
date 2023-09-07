/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:05:22 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/07 16:55:05 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update(void *param)
{
	t_cubed	*cubed;

	cubed = param;
	if (cubed->mouse == 1)
		mlx_set_cursor_mode(cubed->mlx.mlx, MLX_MOUSE_NORMAL);
	if (cubed->mouse == 0)
		mlx_set_cursor_mode(cubed->mlx.mlx, MLX_MOUSE_HIDDEN);
	if (cubed->mouse == 0)
		mouse_rotate(cubed);
	check_keys(cubed);
	draw(cubed);
}

void	cub3d(t_cubed *cubed)
{
	cubed->map.map_s = 24;
	find_player_position(cubed);
	load_text(cubed);
	cubed->player.dx = cos(deg_to_rad(cubed->player.pa));
	cubed->player.dy = -sin(deg_to_rad(cubed->player.pa));
	init_mlx(cubed);
	draw(cubed);
	mlx_loop_hook(cubed->mlx.mlx, &update, cubed);
	mlx_loop(cubed->mlx.mlx);
}

int	main(int argc, char **argv)
{
	t_cubed	cubed;

	cubed.north = NULL;
	cubed.south = NULL;
	cubed.west = NULL;
	cubed.east = NULL;
	cubed.mlx.mlx = NULL;
	cubed.mlx.image = NULL;
	if (argc != 2)
		return (1);
	map_parsing(&cubed, argv[1]);
	cub3d(&cubed);
	free_all(&cubed);
	return (0);
}
