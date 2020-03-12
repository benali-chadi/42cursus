/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:42 by cbenali-          #+#    #+#             */
/*   Updated: 2020/03/01 20:20:31 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		key_destroy(int key, void *ptr)
{
	key = (int)ptr;
	to_free();
	mlx_destroy_window(g_info.mlx_ptr, g_info.win_ptr);
	exit(0);
	return(0);
}

int		key_press(int key, t_player *player)
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
	if (key == 126 && g_drw_wll.t <= g_info.win_height)
		g_drw_wll.t += 30;
	if (key == 125 && g_drw_wll.t >= -(g_info.win_height))
		g_drw_wll.t -= 30;
	if (key == 53)
	{
		mlx_destroy_window(g_info.mlx_ptr, g_info.win_ptr);
		to_free();
		exit(0);
	}
	return (0);
}

int		key_release(int key, t_player *player)
{
	if (key == 1 || key == 13 || key == 2 || key == 0)
		player->walk_direction = 0;
	if (key == 124 || key == 123)
		player->turn_direction = 0;
	return (0);
}

void	render(t_player *player)
{
	init_img();
	draw_map(player);
	update_spr_dis(*player);
	cast_all_rays(*player);
	render_3d(player->direction, *player);
	if (g_info.save)
	{
		bmp_save();
		exit(0);
	}
	mlx_put_image_to_window(g_info.mlx_ptr,
			g_info.win_ptr, g_info.img_ptr, 0, 0);
}

int		move(t_player *player)
{
	if (player->walk_direction == 1)
		if (!has_wall((player->y_p + INC_Y_UD * 10),
		(player->x_p + INC_X_UD * 10)))
			add_to_pl(&player->x_p, &player->y_p, INC_X_UD, INC_Y_UD);
	if (player->walk_direction == -1)
		if (!has_wall((player->y_p - INC_Y_UD * 10),
		(player->x_p - INC_X_UD * 10)))
			sub_frm_pl(&player->x_p, &player->y_p, INC_X_UD, INC_Y_UD);
	if (player->walk_direction == 2)
		if (!has_wall((player->y_p + INC_Y_LR * 10),
		(player->x_p + INC_X_LR * 10)))
			add_to_pl(&player->x_p, &player->y_p, INC_X_LR, INC_Y_LR);
	if (player->walk_direction == -2)
		if (!has_wall((player->y_p - INC_Y_LR * 10),
		(player->x_p - INC_X_LR * 10)))
			sub_frm_pl(&player->x_p, &player->y_p, INC_X_LR, INC_Y_LR);
	player->direction += player->turn_direction;
	render(player);
	return (0);
}
