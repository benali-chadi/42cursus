/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:30 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:40:32 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void init_img()
{
    int bpp;
	int size_line;
	int endian;
    
    mlx_destroy_image(g_info.mlx_ptr, g_info.img_ptr);
    mlx_clear_window(g_info.mlx_ptr, g_info.win_ptr);
    g_info.img_ptr = mlx_new_image(g_info.mlx_ptr, g_info.win_width, g_info.win_height);
	g_info.img_data = (int *)mlx_get_data_addr(g_info.img_ptr, &bpp, &size_line, &endian);
}

void	put_pix(int x, int y, int color)
{
    if (x >= 0 && x < g_info.win_width && y >= 0 && y < g_info.win_height)
        g_info.img_data[x + (y * g_info.win_width)] = color;
}

void    init_sprite(int i, int j, t_player player)
{
    g_sprite--;
    g_spt[g_sprite].y = i * TILE_SIZE;
    g_spt[g_sprite].x = j * TILE_SIZE;
    g_spt[g_sprite].distance = dist_p(g_spt[g_sprite].x, g_spt[g_sprite].y, player.x_p, player.y_p);
}

void    update_spr_dis(t_player player)
{
    int i;
    int j;
    t_spt temp;

    i = -1;
    while (++i < g_count)
        g_spt[i].distance = dist_p(g_spt[i].x, g_spt[i].y, player.x_p, player.y_p);
    /*
    **Sort the array
    */
    i = -1;
    while (++i < g_count)
    {
        j = -1;
        while (++j < g_count - i)
            if (g_spt[j].distance < g_spt[j + 1].distance)
            {
                temp = g_spt[j];
                g_spt[j] = g_spt[j + 1];
                g_spt[j + 1] = temp;
            }
    }
}

void    draw_map(t_player *player)
{
    int i;
    int j;
    // int x;
    // int y;

    i = 0;
    j = 0;
    player->x_m = 0;
    player->y_m = 0;
    while (i < g_info.map_y)
    {
        j = 0;
        while(j < g_info.map_x)
        {
            if (ft_isalpha(g_map[i][j]) && !g_info.count)
                init_player(player, g_map[i][j]);
            if (g_map[i][j] == 2 && g_sprite)
                init_sprite(i, j, *player);
            player->x_m += TILE_SIZE;
            j++;
        }
        player->x_m = 0;
        player->y_m += TILE_SIZE;
        i++;
    }
}
