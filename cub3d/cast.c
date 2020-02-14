/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:39:56 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/15 00:43:33 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	horz_inter(t_ray_hit *horz, t_player player, int id, float angle)
{
	horz->y_inte = floor(player.y_p / TILE_SIZE) * TILE_SIZE;
	horz->y_inte += g_rays[id].is_ray_facing_down ? TILE_SIZE : 0;
	horz->to_check = g_rays[id].is_ray_facing_up ? -1 : 0;
	horz->x_inte = player.x_p - (player.y_p -
			horz->y_inte) / tan(angle);
	horz->y_step = TILE_SIZE;
	horz->y_step *= g_rays[id].is_ray_facing_up ? -1 : 1;
	horz->x_step = horz->y_step / tan(angle);
	while (horz->x_inte >= 0 && horz->x_inte < g_info.win_x &&
	horz->y_inte >= 0 && horz->y_inte < g_info.win_y)
	{
		if (has_wall_ray(horz->y_inte + horz->to_check, horz->x_inte))
		{
			horz->hit_x = horz->x_inte;
			horz->hit_y = horz->y_inte;
			horz->found_hit = 1;
			break ;
		}
		else
		{
			horz->x_inte += horz->x_step;
			horz->y_inte += horz->y_step;
		}
	}
}

void	vert_inter(t_ray_hit *vert, t_player player, int id, float angle)
{
	vert->x_inte = floor(player.x_p / TILE_SIZE) * TILE_SIZE;
	vert->x_inte += g_rays[id].is_ray_facing_right ? TILE_SIZE : 0;
	vert->to_check = g_rays[id].is_ray_facing_left ? -1 : 0;
	vert->y_inte = player.y_p - (player.x_p - vert->x_inte) * tan(angle);
	vert->x_step = TILE_SIZE;
	vert->x_step *= g_rays[id].is_ray_facing_left ? -1 : 1;
	vert->y_step = vert->x_step * tan(angle);
	while (vert->x_inte >= 0 && vert->x_inte < g_info.win_x &&
	vert->y_inte >= 0 && vert->y_inte < g_info.win_y)
	{
		if (has_wall_ray(vert->y_inte, vert->x_inte + vert->to_check))
		{
			vert->hit_x = vert->x_inte;
			vert->hit_y = vert->y_inte;
			vert->found_hit = 1;
			break ;
		}
		else
		{
			vert->x_inte += vert->x_step;
			vert->y_inte += vert->y_step;
		}
	}
}

void	give_values(t_ray_hit inter, float angle, int id, float distance)
{
	g_rays[id].distance = distance;
	g_rays[id].wall_hit_x = inter.hit_x;
	g_rays[id].wall_hit_y = inter.hit_y;
	g_rays[id].ray_angle = angle;
}

void	cast_ray(float angle, int stripid, t_player player)
{
	t_ray_hit	horz;
	t_ray_hit	vert;
	float		horz_hit_distance;
	float		vert_hit_distance;

	vert.found_hit = 0;
	horz.found_hit = 0;
	horz_inter(&horz, player, stripid, angle);
	vert_inter(&vert, player, stripid, angle);
	horz_hit_distance = horz.found_hit ? dist_p(player.x_p, player.y_p,
	horz.hit_x, horz.hit_y) : INT_MAX;
	vert_hit_distance = vert.found_hit ? dist_p(player.x_p, player.y_p,
	vert.hit_x, vert.hit_y) : INT_MAX;
	if (vert_hit_distance < horz_hit_distance)
	{
		give_values(vert, angle, stripid, vert_hit_distance);
		g_rays[stripid].is_vertical = 1;
	}
	else
	{
		give_values(horz, angle, stripid, horz_hit_distance);
		g_rays[stripid].is_vertical = 0;
	}
}

void	cast_all_rays(t_player player)
{
	int		i;
	float	ray_angle;

	ray_angle = (player.direction - 30) * VAL;
	i = 0;
	while (i < g_info.win_width)
	{
		g_rays[i].is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
		g_rays[i].is_ray_facing_up = !g_rays[i].is_ray_facing_down;
		g_rays[i].is_ray_facing_right = ray_angle < 0.5 * PI ||
			ray_angle > 1.5 * PI;
		g_rays[i].is_ray_facing_left = !g_rays[i].is_ray_facing_right;
		ray_angle = normalize_angle(ray_angle);
		cast_ray(ray_angle, i, player);
		ray_angle += FOV / g_info.win_width;
		i++;
	}
}
