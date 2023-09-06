/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:31:13 by atuliara          #+#    #+#             */
/*   Updated: 2023/09/06 11:54:42 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_text(t_cubed *cubed)
{
	cubed->north = mlx_load_png(cubed->map.path_to_north);
	if (!cubed->north)
		error_exit(cubed, NULL);
	cubed->south = mlx_load_png(cubed->map.path_to_south);
	if (!cubed->south)
		error_exit(cubed, NULL);
	cubed->east = mlx_load_png(cubed->map.path_to_east);
	if (!cubed->east)
		error_exit(cubed, NULL);
	cubed->west = mlx_load_png(cubed->map.path_to_west);
	if (!cubed->west)
		error_exit(cubed, NULL);
}

void	toggle_mouse(mlx_key_data_t keydata, void *param)
{
	t_cubed	*cubed;

	cubed = param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		if (cubed->mouse == 0)
			cubed->mouse = 1;
		else if (cubed->mouse == 1)
			cubed->mouse = 0;
	}
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
	{
		free_all(cubed);
		exit (0);
	}
	mlx_key_hook(cubed->mlx.mlx, &toggle_mouse, cubed);
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

void	check_for_player(t_cubed *cubed, int y, int x)
{
	int	xo;
	int	yo;

	xo = x * cubed->map.map_s;
	yo = y * cubed->map.map_s;
	if (cubed->map.map[y * cubed->map.map_x + x] == 3)
	{
		cubed->player.px = xo + cubed->map.map_s / 2;
		cubed->player.py = yo + cubed->map.map_s / 2;
		cubed->player.og_x = xo + cubed->map.map_s / 2;
		cubed->player.og_y = yo + cubed->map.map_s / 2;
		cubed->map.map[y * cubed->map.map_x + x] = 0;
	}
}
