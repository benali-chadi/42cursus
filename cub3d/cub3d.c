#include "cube3d.h"

void init_pl_map(t_player *player)
{
    player->turn_direction = 0;
    player->walk_direction = 0;
    // player->direction = 20;
    player->color = 0x48CFAF;
}

// FOR CHARACTER //

void    put_character(t_player player)
{
    float r;
	float phi;
    int or_x;
    int or_y;

    or_x = player.x_p;
    or_y = player.y_p;
	r = 2;
	phi = 0;
	while (phi <= 360)
	{
		player.x_p = or_x + (r * cos(phi * VAL));
		player.y_p = or_y + (r * sin(phi * VAL));
		put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, player.color);
		phi += 0.1;
	}
   
    while (r < 60)
    {
        put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, 0xff0000);
        player.x_p = or_x + (r * cos(player.direction * VAL));
        player.y_p = or_y + (r * sin(player.direction * VAL));
        r++;
    }
    player.x_p = or_x;
    player.y_p = or_y;
    
    // Cast drawing

    int i = 0;
    // cast_all_rays(player);
    while (i < info.win_width)
    {
        r = 0;
        while (r < rays[i].distance)
        {
            player.x_p = or_x + (r * cos(rays[i].ray_angle));
            player.y_p = or_y + (r * sin(rays[i].ray_angle));
            put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, player.color);
            r++;
        }
        i++;
    }
    // render_3d();
}

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
            // else if (map[i][j] == 2)
            //     put_square(*player, 0x00CF91);
            // else if (map[i][j] == 3)
            //     put_square(*player, 0x7367F0);
            // else if (map[i][j] == 4)
            //     put_square(*player, 0xB6BCF2);
            else if (ft_isalpha(map[i][j]) && !info.count)
            {
                player->x_p = player->x_m;
                player->y_p = player->y_m;
                if (map[i][j] == 'N')
                    player->direction = 270;
                else if (map[i][j] == 'S')
                    player->direction = 90;
                else if (map[i][j] == 'W')
                    player->direction = 0;
                else if (map[i][j] == 'E')
                    player->direction = 180;
                info.count++;
            }
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
    // Initialization
    init_pl_map(&player);
    // Move
    mlx_hook(info.win_ptr, 2, 1L<<0, key_press, &player);
    mlx_hook(info.win_ptr, 3, 1L<<1, key_release, &player);
    mlx_hook(info.win_ptr, 17, 0L, key_destroy, (void *)0);
    mlx_loop_hook(info.mlx_ptr, move, &player);
	mlx_loop(info.mlx_ptr);
    return(0);
}