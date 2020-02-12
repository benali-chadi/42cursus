/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_spt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:41:24 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:41:29 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    render_spt(int x, int y, int sp_size, int k)
{
    int color;
    int a;
    int i;
    int j;
    
    i = 0;
    if (!(g_spt[k].ptr = mlx_xpm_file_to_image(g_info.mlx_ptr, g_info.paths.sp, &g_spt[k].x_s, &g_spt[k].y_s)))
    {
        ft_putstr_fd("Error\nSprite texture file not valid\n", 1);
        exit(-1);
    }
    g_spt[k].data = (int *)mlx_get_data_addr(g_spt[k].ptr, &a, &a, &a);
    while (i++ < sp_size)
    {
        if (x + i < 0 || x + i > g_info.win_width)
            continue;
        if(g_spt[k].distance >= g_rays[x + i].distance)
            continue;
        j = 0;
        while (j++ < sp_size)
        {
            color = g_spt[k].data[g_spt[k].x_s * (j * g_spt[k].y_s / sp_size) + (i * g_spt[k].x_s / sp_size)];
            if (color != 0)
                put_pix(x + i, y + j, color);
        }
    }
}

void    ft_sprite(t_player player, int i)
{
    float   sp_size;
    float   x_inter;
    float   y_inter;
    float   sp_angle;
    
    sp_angle = atan2(g_spt[i].y - player.y_p, g_spt[i].x - player.x_p);
    while (sp_angle - (player.direction * VAL) > PI)
        sp_angle -= TWO_PI;
    while (sp_angle - (player.direction * VAL) < -PI)
        sp_angle += TWO_PI;
    if (g_info.win_height > g_info.win_width)
        sp_size = (g_info.win_height / g_spt[i].distance) * TILE_SIZE;
    else
        sp_size = (g_info.win_width / g_spt[i].distance) * TILE_SIZE;
    y_inter = g_info.win_height / 2 - sp_size / 2;
    x_inter = (sp_angle - player.direction * VAL) / FOV * g_info.win_width + (g_info.win_width / 2 - sp_size / 2);
    render_spt(x_inter, y_inter, sp_size, i);
}
