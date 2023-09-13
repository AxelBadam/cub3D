/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:31:17 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/13 15:32:29 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_cubed *cubed)
{
	cubed->mouse = 1;
	cubed->mlx.mlx = mlx_init(WIDTH, 980, "cub3d", false);
	if (!(cubed->mlx.mlx))
		error_exit(cubed, "MLX ERROR\n");
}
