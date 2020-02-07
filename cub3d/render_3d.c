/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:41:13 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:41:14 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    draw_wall(int x, float wall_height, int i)
{
    drw_wll.y = (info.win_height / 2) - (wall_height / 2);
    drw_wll.top_pixel = drw_wll.y;
    drw_wll.y_end = drw_wll.y + wall_height;
    drw_wll.x_end = x + WALL_WIDTH;
    drw_wll.or_x = x;
    if (rays[x].is_vertical)
        drw_wll.x_tex = (int)rays[x].wall_hit_y % TILE_SIZE;
    else
        drw_wll.x_tex = (int)rays[x].wall_hit_x % TILE_SIZE;
    while (drw_wll.y < drw_wll.y_end)
    {
        x = drw_wll.or_x;
        drw_wll.y_tex = (drw_wll.y - drw_wll.top_pixel) * ((float)tex[i].img_height / wall_height);
        while (x < drw_wll.x_end)
        {
            drw_wll.color = tex[i].tex[drw_wll.x_tex + (drw_wll.y_tex * tex[i].img_width)];
            if (x >= 0 && x < info.win_width && drw_wll.y >= 0 && drw_wll.y < info.win_height)
                put_pix(x, drw_wll.y, drw_wll.color);
            x++;
        }
        drw_wll.y++;
    }
}

void    draw_flr()
{
    int y;
    int x;

    y = info.win_height / 2;
    while (y < info.win_height)
    {
        x = 0;
        while (x < info.win_width)
        {
            if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
                put_pix(x, y, info.flr_co);
            x++;
        }
        y++;
    }
}

void    draw_cel()
{
    int x;
    int y;
    int y_end;

    y = 0;
    y_end = info.win_height / 2;
    while (y < y_end)
    {
        x = 0;
        while (x < info.win_width)
        {
            if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
                put_pix(x, y, info.cel_co);
            x++;
        }
        y++;
    }
}

void    init_tex(int i)
{
    if (tex[i].ptr)
        mlx_destroy_image(info.mlx_ptr, tex[i].ptr);
    if (i == 0)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/mossy.xpm", &tex[i].img_width, &tex[i].img_height);
    else if (i == 1)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/colorstone.xpm", &tex[i].img_width, &tex[i].img_height);
    else if (i == 2)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/eagle.xpm", &tex[i].img_width, &tex[i].img_height);
    else if (i == 3)
        tex[i].ptr = mlx_xpm_file_to_image(info.mlx_ptr, "textures/redbrick.xpm", &tex[i].img_width, &tex[i].img_height);
    tex[i].tex = (int *)mlx_get_data_addr(tex[i].ptr, &tex[i].bpp, &tex[i].size_line, &tex[i].endian);
}

void    render_3d(float direction, t_player player)
{
    int i;
    float dist_proj;
    float wall_height;
    float distance;

    draw_flr();
    draw_cel();
    i = -1;
    while (++i < 4)
        init_tex(i);
    dist_proj = (info.win_width / 2) / tan(FOV_ANGLE / 2);
    i = 0;
    while (i < info.win_width)
    {
        distance = rays[i].distance * cos(rays[i].ray_angle - (direction * VAL));
        wall_height = (TILE_SIZE / distance) * dist_proj;
        if (rays[i].is_ray_facing_up && !rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 0);
        else if (rays[i].is_ray_facing_down && !rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 1);
        else if (rays[i].is_ray_facing_left && rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 2);
        else if (rays[i].is_ray_facing_right && rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 3);
        i++;
    }
    i = -1;
    while (++i < g_count)
        ft_sprite(player, i);
}
