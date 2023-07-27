/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekoljone <ekoljone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:18:08 by ekoljone          #+#    #+#             */
/*   Updated: 2023/07/27 18:28:41 by ekoljone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct s_map
{
	char	**map;
	char	*path_to_north;
	char	*path_to_south;
	char	*path_to_west;
	char	*path_to_east;
	int		floor_color[3];
	int		cealing_color[3];
} t_map;

typedef struct s_cubed
{
	struct s_map map;
} t_cubed;
