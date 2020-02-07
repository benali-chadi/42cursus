/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:41:38 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:41:40 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int     num(int n)
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

int     has_wall(float y, float x)
{
    if (y > 0 && y < info.win_y && x > 0 && x < info.win_x)
        return (map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0 && 
        !ft_isalpha(map[(int)y / TILE_SIZE][(int)x / TILE_SIZE]));
    return (1);
}

int     has_wall_ray(float y, float x)
{
    if (y > 0 && y < info.win_y && x > 0 && x < info.win_x)
        return (map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == 1);
    return (1);
}

float   dist_p(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float   normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    angle += (angle < 0) ? TWO_PI : 0;
    return (angle);
}

int     normalize_angle_deg(int angle)
{
    angle = angle % 360;
    angle += (angle < 0) ? 360 : 0;
    return (angle);
}
