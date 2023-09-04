/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:31:13 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/04 13:17:45 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	load_text(t_cubed *cubed)
{
	if (!mlx_load_png(cubed->map.path_to_north))
		exit (1);
	if (!mlx_load_png(cubed->map.path_to_south))
		exit (1);
	if (!mlx_load_png(cubed->map.path_to_east))
		exit (1);
	if (!mlx_load_png(cubed->map.path_to_west))
		exit (1);
	cubed->north = mlx_load_png(cubed->map.path_to_north);
	cubed->south = mlx_load_png(cubed->map.path_to_south);
	cubed->east = mlx_load_png(cubed->map.path_to_east);
	cubed->west = mlx_load_png(cubed->map.path_to_west);
}

void	check_keys(t_cubed *cubed)
{
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_W))
		move_player(cubed, 'W');
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_A))
		move_player(cubed, 'A');
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_S))
		move_player(cubed, 'S');
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_D))
		move_player(cubed, 'D');
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_LEFT))
		rotate_player(cubed, MLX_KEY_LEFT);
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_RIGHT))
		rotate_player(cubed, MLX_KEY_RIGHT);
	if (mlx_is_key_down(cubed->mlx.mlx, MLX_KEY_ESCAPE))
		exit (0);
}

uint32_t	*get_text_color(mlx_texture_t *texture)
{
	int				i;
	unsigned int	pos;
	uint8_t			rgb[4];
	uint32_t		*colors;

	i = 0;
	colors = malloc(sizeof(uint32_t) * (texture->width + 1)
			* (texture->height + 1));
	if (colors == NULL)
		printf("yo");
	pos = 0;
	while (pos < texture->width * texture->height * texture->bytes_per_pixel)
	{
		rgb[0] = texture->pixels[pos];
		rgb[1] = texture->pixels[pos + 1];
		rgb[2] = texture->pixels[pos + 2];
		rgb[3] = texture->pixels[pos + 3];
		colors[i] = (rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + rgb[3];
		pos += texture->bytes_per_pixel;
		i++;
	}
	return (colors);
}

void	find_player_position(t_cubed *cubed)
{
	int	i = 0;
	int	x = 0;
	int y = 0;
	int xo = 0;
	int yo = 0;
	
	while (y < cubed->map.mapY)
	{
		while (x < cubed->map.mapX)
		{
			xo = x * cubed->map.mapS;
			yo = y * cubed->map.mapS;
			if (cubed->map.map[y * cubed->map.mapX + x] == 3)
			{
				cubed->player.px = xo + cubed->map.mapS / 2;
				cubed->player.py = yo + cubed->map.mapS / 2;
				cubed->player.og_x = xo + cubed->map.mapS / 2;
				cubed->player.og_y = yo + cubed->map.mapS / 2;
				cubed->map.map[y * cubed->map.mapX + x] = 0;
			}
			x++;
			i++;
		}
		x = 0;
		y++;
	}
}



/*
void	mouse_rotate(t_cubed *cubed)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cubed->mlx.mlx, &x, &y);
	x -= WIDTH / 2;
	cubed->player.pa += (float)x / 4000 * 10;
	mlx_set_mouse_pos(cubed->mlx.mlx, WIDTH / 2, HEIGHT / 2);
}*/