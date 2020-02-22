/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 00:16:54 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/15 00:17:59 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	dist_p(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_exit(char *msg)
{
	ft_putstr_fd(msg, 1);
	to_free();
	exit(-1);
}

void	add_to_pl(float *x_p, float *y_p, float x_inc, float y_inc)
{
	*x_p += x_inc * 3;
	*y_p += y_inc * 3;
}

void	sub_frm_pl(float *x_p, float *y_p, float x_inc, float y_inc)
{
	*x_p -= x_inc * 3;
	*y_p -= y_inc * 3;
}

void	check_wall_dir(float wall_height, int i)
{
	if (g_rays[i].is_ray_facing_up && !g_rays[i].is_vertical)
		draw_wall(i * WALL_WIDTH, wall_height, 0);
	else if (g_rays[i].is_ray_facing_down && !g_rays[i].is_vertical)
		draw_wall(i * WALL_WIDTH, wall_height, 1);
	else if (g_rays[i].is_ray_facing_left && g_rays[i].is_vertical)
		draw_wall(i * WALL_WIDTH, wall_height, 2);
	else if (g_rays[i].is_ray_facing_right && g_rays[i].is_vertical)
		draw_wall(i * WALL_WIDTH, wall_height, 3);
}
