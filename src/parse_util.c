/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:58:19 by ekoljone          #+#    #+#             */
/*   Updated: 2023/09/06 12:01:13 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_direction(char index)
{
	if (index == 'W' || index == 'S'
		|| index == 'E' || index == 'N')
		return (1);
	return (0);
}

void	check_index_spot(t_cubed *cubed, char index)
{
	if (index != '1' && index != '0'
		&& index != 'W' && index != 'E'
		&& index != 'S' && index != 'N'
		&& !ft_is_white_space(index))
		error_exit(cubed, "INVALID MAP\n");
}

void	get_player_angle(t_cubed *cubed, char direction)
{
	if (direction == 'W')
		cubed->player.pa = 180;
	else if (direction == 'E')
		cubed->player.pa = 0;
	else if (direction == 'S')
		cubed->player.pa = 270;
	else if (direction == 'N')
		cubed->player.pa = 90;
}

int	iterate_to_newline(char *row)
{
	int	ctr;

	ctr = 0;
	while (row[ctr] && row[ctr] != '\n')
		ctr++;
	return (ctr);
}

int	check_for_empty_row(char *row)
{
	int	index;

	index = 0;
	while (row[index])
	{
		if (!ft_is_white_space(row[index++]))
			return (0);
	}
	return (1);
}
