/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:42 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:40:50 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int     key_destroy(int key, void *ptr)
{
    key = (int)ptr;
    mlx_destroy_window(g_info.mlx_ptr, g_info.win_ptr);
    exit(0);
}

int     key_press(int key, t_player *player)
{
    if (key == 13)
        player->walk_direction = 1; 
    if (key == 1)
        player->walk_direction = -1;
    if (key == 0)
        player->walk_direction = -2;
    if (key == 2)
        player->walk_direction = 2;
    if (key == 124)
        player->turn_direction = 3;
    if (key == 123)
        player->turn_direction = -3;
    if (key == 53)
    {
        mlx_destroy_window(g_info.mlx_ptr, g_info.win_ptr);
        exit(0);
    }
    return (0);
}

int     key_release(int key, t_player *player)
{
    if (key == 1 || key == 13 || key == 2 || key == 0)
        player->walk_direction = 0;
    if (key == 124 || key == 123)
        player->turn_direction = 0;
    return (0);
}

void    render(t_player *player)
{
    init_img();
    draw_map(player);
    update_spr_dis(*player);
    cast_all_rays(*player);
    render_3d(player->direction, *player);
    mlx_put_image_to_window(g_info.mlx_ptr, g_info.win_ptr, g_info.img_ptr, 0, 0);
}

int     move(t_player *player)
{
    if (player->walk_direction == 1)
    {
        if (!has_wall((player->y_p + INCREMENT_Y_UD * 10), (player->x_p + INCREMENT_X_UD * 10)))
        {
            player->y_p += INCREMENT_Y_UD;
            player->x_p += INCREMENT_X_UD; 
        }
    }
    if (player->walk_direction == -1)
    {
        if (!has_wall((player->y_p - INCREMENT_Y_UD * 10), (player->x_p - INCREMENT_X_UD * 10)))
        {
            player->y_p -= INCREMENT_Y_UD;
            player->x_p -= INCREMENT_X_UD; 
        }
    }
    if (player->walk_direction == 2)
        if (!has_wall((player->y_p + INCREMENT_Y_LR * 10), (player->x_p + INCREMENT_X_LR * 10)))
        {
            player->y_p += INCREMENT_Y_LR;
            player->x_p += INCREMENT_X_LR;
        }
    if (player->walk_direction == -2)
        if (!has_wall((player->y_p - INCREMENT_Y_LR * 10), (player->x_p - INCREMENT_X_LR * 10)))
        {
            player->y_p -= INCREMENT_Y_LR;
            player->x_p -= INCREMENT_X_LR;
        }
    player->direction += player->turn_direction;
    render(player);
    return (0);
}
