#include "cube3d.h"

void init_player(t_player *player, int i)
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

// FOR CHARACTER //

void draw_map(t_player *player)
{
    int i;
    int j;

    i = 0;
    j = 0;
    player->x_m = 0;
    player->y_m = 0;
    while (i < info.map_y)
    {
        j = 0;
        while(j < info.map_x)
        {
            if(map[i][j] == 1)
                put_square(*player, 0x0351C1, 1);
            else if (ft_isalpha(map[i][j]) && !info.count)
                init_player(player, map[i][j]);
            else
                put_square(*player, 0x0351C1, 0);
            player->x_m += info.tile_size_x;
            j++;
        }
        player->x_m = 0;
        player->y_m += info.tile_size_y;
        i++;
    }
}

int main(int ac, char **av)
{
    t_player player;
    int     fd;

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
    read_file(fd);
    // int i = 0;
    // int j;

    // while (i < info.map_y)
    // {
    //     j = 0;
    //     while (j < info.map_x)
    //     {
    //         printf("map[%d][%d] : %d\n", i, j, map[i][j]);
    //         j++;
    //     }
    //     i++;
    // }
    info.count = 0;
    info.mlx_ptr = mlx_init();
	info.win_ptr = mlx_new_window(info.mlx_ptr, info.win_width, info.win_height, "mlx 1337");
    info.img_ptr = mlx_new_image(info.mlx_ptr, info.win_width, info.win_height);
    // Move
    mlx_hook(info.win_ptr, 2, 1L<<0, key_press, &player);
    mlx_hook(info.win_ptr, 3, 1L<<1, key_release, &player);
    mlx_hook(info.win_ptr, 17, 0L, key_destroy, (void *)0);
    mlx_loop_hook(info.mlx_ptr, move, &player);
	mlx_loop(info.mlx_ptr);
    return(0);
}