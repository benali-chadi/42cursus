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
    info.count++;
}

void    setup(int fd)
{
    read_file(fd);
    count = sprite;
    info.count = 0;
    info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, info.win_width, info.win_height, "mlx 1337");
    info.img_ptr = mlx_new_image(info.mlx_ptr, info.win_width, info.win_height);
    spt = (t_spt *)malloc(sizeof(t_spt) * sprite);
}

void    update(t_player *player)
{
    mlx_hook(info.win_ptr, 2, 1L<<0, key_press, player);
    mlx_hook(info.win_ptr, 3, 1L<<1, key_release, player);
    mlx_hook(info.win_ptr, 17, 0L, key_destroy, (void *)0);
    mlx_loop_hook(info.mlx_ptr, move, player);
}

int     main(int ac, char **av)
{
    t_player    player;
    int         fd;

    sprite = 0;
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
    setup(fd);
    update(&player);
	mlx_loop(info.mlx_ptr);
    return(0);
}