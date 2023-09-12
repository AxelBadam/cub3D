/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:35 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/12 14:32:55 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_outlines(t_cubed *cubed)
{
	int	y;
	int	x;

	y = 4;
	while (y < 153)
	{
		x = 4;
		while (x < 153)
		{
			my_pixel_put(cubed->mlx.image, x++, y, 0x000000FF);
		}
		y++;
	}
}

void	my_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (y < HEIGHT && y >= 0 && x < WIDTH && x >= 0)
		mlx_put_pixel(image, x, y, color);
}
