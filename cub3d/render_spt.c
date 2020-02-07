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
    int i = 0;
    int j;
    int x_s, y_s;
    
    spt[k].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/pillar.xpm", &x_s, &y_s);
    spt[k].data = (int *)mlx_get_data_addr(spt[k].ptr, &a, &a, &a);

    while (i++ < sp_size)
    {
        if (x + i < 0 || x + i > info.win_width)
            continue;
        if(spt[k].distance >= rays[x + i].distance)
            continue;
        j = 0;
        while (j++ < sp_size)
        {
            color = spt[k].data[x_s * (j * y_s / sp_size) + (i * x_s / sp_size)];
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
    
    sp_angle = atan2(spt[i].y - player.y_p, spt[i].x - player.x_p);
    while (sp_angle - (player.direction * VAL) > PI)
        sp_angle-= 2 * PI;
    while (sp_angle - (player.direction * VAL) < -PI)
        sp_angle+= 2 * PI;
    if (info.win_height > info.win_width)
        sp_size = (info.win_height / (float)spt[i].distance) * TILE_SIZE;
    else
        sp_size = (info.win_width / (float)spt[i].distance) * TILE_SIZE;
    y_inter = info.win_height / 2 - sp_size / 2;
    x_inter = (sp_angle - player.direction * VAL) / FOV_ANGLE * info.win_width + (info.win_width / 2 - sp_size / 2);
    render_spt(x_inter, y_inter, sp_size, i);
}
