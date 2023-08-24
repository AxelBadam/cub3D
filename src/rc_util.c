/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:53:24 by atuliara          #+#    #+#             */
/*   Updated: 2023/08/24 16:47:03 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float degToRad(float a) 
{ 
	return (a*M_PI/180.0);
}

float distance(int ax,int ay,int bx,int by, float ang)
{ 
	return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);
}

float FixAng(float a)
{
	if(a > 359)
		a -= 360;
 	if(a < 0)
 		a += 360;
 	return a;
}