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
    // if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
        info.img_data[x + (y * info.win_width)] = color;
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
            player->x_m += TILE_SIZE;
            j++;
        }
        player->x_m = 0;
        player->y_m += TILE_SIZE;
        i++;
    }
}
