/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/08/02 16:07:27 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

char	**append_2d(char **twod, char *str_to_add);
void	free_string_array(char **array);
int		get_2d_array_size(char **array);

typedef struct s_map
{
	char		**map;
	char		*path_to_north;
	char		*path_to_south;
	char		*path_to_west;
	char		*path_to_east;
	long int	floor_color;
	long int	cealing_color;
} t_map;

typedef struct s_mlx
{
	mlx_t	*mlx;
	mlx_image_t	*image;
} t_mlx;

typedef struct s_cubed
{
	struct s_map map;
	struct s_mlx mlx;
} t_cubed;
