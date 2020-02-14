/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:39:56 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:39:58 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void horz_inter(t_ray_hit *horz, t_player player, int stripid, float ray_angle)
{
    float next_touch_x;
    float next_touch_y;

    horz->y_intercept = floor(player.y_p / TILE_SIZE) * TILE_SIZE;
    horz->y_intercept += g_rays[stripid].is_ray_facing_down ? TILE_SIZE : 0;
    horz->to_check = g_rays[stripid].is_ray_facing_up ? -1 : 0;
    horz->x_intercept = player.x_p - (player.y_p - horz->y_intercept) / tan(ray_angle);
    horz->y_step = TILE_SIZE;
    horz->y_step *= g_rays[stripid].is_ray_facing_up ? -1 : 1;
    horz->x_step = horz->y_step / tan(ray_angle);
    next_touch_x = horz->x_intercept;
    next_touch_y = horz->y_intercept;
    while (next_touch_x >= 0 && next_touch_x < g_info.win_x && next_touch_y >= 0 && next_touch_y < g_info.win_y)
    {
        if(has_wall_ray(next_touch_y + horz->to_check, next_touch_x))
        {
            horz->wall_hit_x = next_touch_x;
            horz->wall_hit_y = next_touch_y;
            horz->wall_content = g_map[(int)next_touch_y / TILE_SIZE][(int)next_touch_x / TILE_SIZE];
            horz->found_hit = 1;
            break;
        }
        else
        {
            next_touch_x += horz->x_step;
            next_touch_y += horz->y_step;
        }
    }
}

void vert_inter(t_ray_hit *vert, t_player player, int stripid, float ray_angle)
{
    float next_touch_x;
    float next_touch_y;

    vert->x_intercept = floor(player.x_p / TILE_SIZE) * TILE_SIZE;
    vert->x_intercept += g_rays[stripid].is_ray_facing_right ? TILE_SIZE : 0;
    vert->to_check = g_rays[stripid].is_ray_facing_left ? -1 : 0;
    vert->y_intercept = player.y_p - (player.x_p - vert->x_intercept) * tan(ray_angle);
    vert->x_step = TILE_SIZE;
    vert->x_step *= g_rays[stripid].is_ray_facing_left ? -1 : 1;
    vert->y_step = vert->x_step * tan(ray_angle);
    next_touch_x = vert->x_intercept;
    next_touch_y = vert->y_intercept;
    while (next_touch_x >= 0 && next_touch_x < g_info.win_x && next_touch_y >= 0 && next_touch_y < g_info.win_y)
    {
        if(has_wall_ray(next_touch_y, next_touch_x + vert->to_check))
        {
            vert->wall_hit_x = next_touch_x;
            vert->wall_hit_y = next_touch_y;
            vert->wall_content = g_map[(int)next_touch_y / TILE_SIZE][(int)next_touch_x / TILE_SIZE];
            vert->found_hit = 1;
            break;
        }
        else
        {
            next_touch_x += vert->x_step;
            next_touch_y += vert->y_step;
        }
    }    
}

void    give_values(t_ray_hit inter, float ray_angle, int stripid, float distance)
{
    g_rays[stripid].distance = distance;
    g_rays[stripid].wall_hit_x = inter.wall_hit_x;
    g_rays[stripid].wall_hit_y = inter.wall_hit_y;
    g_rays[stripid].wall_hit_content = inter.wall_content;
    g_rays[stripid].ray_angle = ray_angle;
}

void    cast_ray(float ray_angle, int stripid, t_player player)
{
    t_ray_hit horz;
    t_ray_hit vert;
    float horz_hit_distance;
    float vert_hit_distance;

    g_rays[stripid].is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
    g_rays[stripid].is_ray_facing_up = !g_rays[stripid].is_ray_facing_down;
    g_rays[stripid].is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    g_rays[stripid].is_ray_facing_left = !g_rays[stripid].is_ray_facing_right;
    vert.found_hit = 0;
    horz.found_hit = 0;
    horz_inter(&horz, player, stripid, ray_angle);
    vert_inter(&vert, player, stripid, ray_angle);
    horz_hit_distance = horz.found_hit
    ? dist_p(player.x_p, player.y_p, horz.wall_hit_x, horz.wall_hit_y)
    : INT_MAX;
    vert_hit_distance = vert.found_hit
    ? dist_p(player.x_p, player.y_p, vert.wall_hit_x, vert.wall_hit_y)
    : INT_MAX;
    if (vert_hit_distance < horz_hit_distance)
    {
        give_values(vert, ray_angle, stripid, vert_hit_distance);
        g_rays[stripid].is_vertical = 1;
    }
    else
    {
        give_values(horz, ray_angle, stripid, horz_hit_distance);
        g_rays[stripid].is_vertical = 0;
    }
}

void    cast_all_rays(t_player player)
{
    int     strip_id;
    float   ray_angle;

    ray_angle = (player.direction - 30) * VAL;
    strip_id = 0;
    while (strip_id < g_info.win_width)
    {        
        ray_angle = normalize_angle(ray_angle);
        cast_ray(ray_angle, strip_id, player);
        ray_angle += FOV / g_info.win_width;
        strip_id++;
    }
}
