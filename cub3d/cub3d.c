/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:08 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/05 16:40:10 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    init_player(t_player *player, int i)
{
    player->turn_direction = 0;
    player->walk_direction = 0;
    player->x_p = player->x_m;
    player->y_p = player->y_m;
    if (i == 'N')
        player->direction = 270;
    else if (i == 'S')
        player->direction = 90;
    else if (i == 'W')
        player->direction = 0;
    else if (i == 'E')
        player->direction = 180;
    player->color = 0x48CFAF;
    g_info.count++;
}

int    setup(int fd)
{
    read_file(fd);
    g_count = g_sprite;
    g_info.count = 0;
    g_info.mlx_ptr = mlx_init();
	g_info.win_ptr = mlx_new_window(g_info.mlx_ptr, g_info.win_width, g_info.win_height, "mlx 1337");
    g_info.img_ptr = mlx_new_image(g_info.mlx_ptr, g_info.win_width, g_info.win_height);
    if(!(g_spt = (t_spt *)malloc(sizeof(t_spt) * g_sprite)))
        return(0);
    return (1);
}

void    update(t_player *player)
{
    mlx_hook(g_info.win_ptr, 2, 1L<<0, key_press, player);
    mlx_hook(g_info.win_ptr, 3, 1L<<1, key_release, player);
    mlx_hook(g_info.win_ptr, 17, 0L, key_destroy, (void *)0);
    mlx_loop_hook(g_info.mlx_ptr, move, player);
}

int     main(int ac, char **av)
{
    t_player    player;
    int         fd;

    g_sprite = 0;
    if (ac < 2)
    {
        perror("Error");
        exit(-1);
    }
    fd = open(av[1], O_RDONLY);
    if (fd < 0 || !check_name(av[1]))
    {
        perror("Error");
        exit(-1);
    }
    if (!(setup(fd)))
    {
        ft_putstr_fd("Eroor\nAllocation error\n", 1);
        exit(-1);
    }
    update(&player);
	mlx_loop(g_info.mlx_ptr);
    return(0);
}
