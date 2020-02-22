/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:40:08 by cbenali-          #+#    #+#             */
/*   Updated: 2020/02/14 23:29:46 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player(t_player *player, int i)
{
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->x_p = player->x_m + (TILE_SIZE / 2);
	player->y_p = player->y_m + (TILE_SIZE / 2);
	if (i == 'N')
		player->direction = 270;
	else if (i == 'S')
		player->direction = 90;
	else if (i == 'W')
		player->direction = 180;
	else if (i == 'E')
		player->direction = 0;
	g_info.count++;
}

int		setup(int fd)
{
	read_file(fd);
	g_count = g_sprite;
	g_info.count = 0;
	g_info.mlx_ptr = mlx_init();
	g_info.win_ptr = mlx_new_window(g_info.mlx_ptr, g_info.win_width,
			g_info.win_height, "mlx 1337");
	g_info.img_ptr = mlx_new_image(g_info.mlx_ptr,
			g_info.win_width, g_info.win_height);
	if (!(g_spt = (t_spt *)m_malloc(sizeof(t_spt) * g_sprite)))
		return (0);
	return (1);
}

void	update(t_player *player)
{
	mlx_hook(g_info.win_ptr, 2, 0, key_press, player);
	mlx_hook(g_info.win_ptr, 3, 0, key_release, player);
	mlx_hook(g_info.win_ptr, 17, 0L, key_destroy, (void *)0);
	mlx_loop_hook(g_info.mlx_ptr, move, player);
}

int		main(int ac, char **av)
{
	t_player	player;
	int			fd;

	g_info.save = 0;
	g_sprite = 0;
	if (ac < 2 || ac > 3)
		ft_exit("Eroor\nNot or more than enough arguments\n");
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || !check_name(av[1]))
		ft_exit("Error\nFile name is invalid\n");
	if (av[2])
	{
		if (!(ft_strncmp(av[2], "--save", 15)))
			g_info.save = 1;
		else
			ft_exit("Error\nSecond argument name not accurate\n");
	}
	if (!(setup(fd)))
		ft_exit("Eroor\nAllocation error\n");
	update(&player);
	mlx_loop(g_info.mlx_ptr);
	return (0);
}
