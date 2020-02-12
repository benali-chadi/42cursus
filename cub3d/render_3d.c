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
    g_drw_wll.y = (g_info.win_height / 2) - (wall_height / 2);
    g_drw_wll.top_pixel = g_drw_wll.y;
    g_drw_wll.y_end = g_drw_wll.y + wall_height;
    g_drw_wll.x_end = x + WALL_WIDTH;
    g_drw_wll.or_x = x;
    if (g_rays[x].is_vertical)
        g_drw_wll.x_tex = (int)g_rays[x].wall_hit_y % TILE_SIZE;
    else
        g_drw_wll.x_tex = (int)g_rays[x].wall_hit_x % TILE_SIZE;
    while (g_drw_wll.y < g_drw_wll.y_end)
    {
        x = g_drw_wll.or_x;
        g_drw_wll.y_tex = (g_drw_wll.y - g_drw_wll.top_pixel) * ((float)g_tex[i].img_height / wall_height);
        while (x < g_drw_wll.x_end)
        {
            g_drw_wll.color = g_tex[i].tex[g_drw_wll.x_tex + (g_drw_wll.y_tex * g_tex[i].img_width)];
            if (x >= 0 && x < g_info.win_width && g_drw_wll.y >= 0 && g_drw_wll.y < g_info.win_height)
                put_pix(x, g_drw_wll.y, g_drw_wll.color);
            x++;
        }
        g_drw_wll.y++;
    }
}

void    draw_flr()
{
    int y;
    int x;

    y = g_info.win_height / 2;
    while (y < g_info.win_height)
    {
        x = 0;
        while (x < g_info.win_width)
        {
            if (x >= 0 && x < g_info.win_width && y >= 0 && y < g_info.win_height)
                put_pix(x, y, g_info.flr_co);
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
    y_end = g_info.win_height / 2;
    while (y < y_end)
    {
        x = 0;
        while (x < g_info.win_width)
        {
            if (x >= 0 && x < g_info.win_width && y >= 0 && y < g_info.win_height)
                put_pix(x, y, g_info.cel_co);
            x++;
        }
        y++;
    }
}

void    init_tex(int i)
{
    if (g_tex[i].ptr)
        mlx_destroy_image(g_info.mlx_ptr, g_tex[i].ptr);
    if (i == 0)
        g_tex[i].ptr = mlx_xpm_file_to_image(g_info.mlx_ptr, g_info.paths.no, &g_tex[i].img_width, &g_tex[i].img_height);
    else if (i == 1)
        g_tex[i].ptr = mlx_xpm_file_to_image(g_info.mlx_ptr, g_info.paths.so, &g_tex[i].img_width, &g_tex[i].img_height);
    else if (i == 2)
        g_tex[i].ptr = mlx_xpm_file_to_image(g_info.mlx_ptr, g_info.paths.we, &g_tex[i].img_width, &g_tex[i].img_height);
    else if (i == 3)
        g_tex[i].ptr = mlx_xpm_file_to_image(g_info.mlx_ptr, g_info.paths.ea, &g_tex[i].img_width, &g_tex[i].img_height);
    g_tex[i].tex = (int *)mlx_get_data_addr(g_tex[i].ptr, &g_tex[i].bpp, &g_tex[i].size_line, &g_tex[i].endian);
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
    dist_proj = (g_info.win_width / 2) / tan(FOV / 2);
    i = 0;
    while (i < g_info.win_width)
    {
        distance = g_rays[i].distance * cos(g_rays[i].ray_angle - (direction * VAL));
        wall_height = (TILE_SIZE / distance) * dist_proj;
        if (g_rays[i].is_ray_facing_up && !g_rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 0);
        else if (g_rays[i].is_ray_facing_down && !g_rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 1);
        else if (g_rays[i].is_ray_facing_left && g_rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 2);
        else if (g_rays[i].is_ray_facing_right && g_rays[i].is_vertical)
            draw_wall(i * WALL_WIDTH, wall_height, 3);
        i++;
    }
    i = -1;
    while (++i < g_count)
        ft_sprite(player, i);
}
