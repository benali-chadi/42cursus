#include "cube3d.h"

void init_img()
{
    int bpp;
	int size_line;
	int endian;
    
    mlx_destroy_image(info.mlx_ptr, info.img_ptr);
    mlx_clear_window(info.mlx_ptr, info.win_ptr);
    info.img_ptr = mlx_new_image(info.mlx_ptr, info.win_width, info.win_height);
	info.img_data = (int *)mlx_get_data_addr(info.img_ptr, &bpp, &size_line, &endian);
}

void	put_pix(int x, int y, int color)
{
    if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
        info.img_data[x + (y * info.win_width)] = color;
}

void    init_sprite(int i, int j, t_player player)
{
    sprite--;
    spt[sprite].y = i * TILE_SIZE;
    spt[sprite].x = j * TILE_SIZE;
    spt[sprite].distance = dist_p(spt[sprite].x, spt[sprite].y, player.x_p, player.y_p);
}

void    update_spr_dis(t_player player)
{
    int i;
    int j;
    t_spt temp;

    i = -1;
    while (++i < count)
        spt[i].distance = dist_p(spt[i].x, spt[i].y, player.x_p, player.y_p);
    /*
    **Sort the array
    */
    i = -1;
    while (++i < count)
    {
        j = -1;
        while (++j < count - i)
            if (spt[j].distance < spt[j + 1].distance)
            {
                temp = spt[j];
                spt[j] = spt[j + 1];
                spt[j + 1] = temp;
            }
    }
}

void    draw_map(t_player *player)
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
            if (ft_isalpha(map[i][j]) && !info.count)
                init_player(player, map[i][j]);
            if (map[i][j] == 2 && sprite)
                init_sprite(i, j, *player);
            player->x_m += TILE_SIZE;
            j++;
        }
        player->x_m = 0;
        player->y_m += TILE_SIZE;
        i++;
    }
}
