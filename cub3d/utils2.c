/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:41:38 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/15 00:14:11 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		num(int n)
{
	int i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		has_wall(float y, float x)
{
	if (y > 0 && y < g_info.win_y && x > 0 && x < g_info.win_x)
		return (g_map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0 &&
		!ft_isalpha(g_map[(int)y / TILE_SIZE][(int)x / TILE_SIZE]));
		return (1);
}

int		has_wall_ray(float y, float x)
{
	if (y > 0 && y < g_info.win_y && x > 0 && x < g_info.win_x)
		return (g_map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == 1);
	return (1);
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	angle += (angle < 0) ? TWO_PI : 0;
	return (angle);
}

int		normalize_angle_deg(int angle)
{
	angle = angle % 360;
	angle += (angle < 0) ? 360 : 0;
	return (angle);
}
