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

void put_square(t_player player, int color, int num)
{
    int d;
    int d2;
    int or_x;
    int or_y;

    or_y = player.y_m;
    or_x = player.x_m;
    d2 = player.y_m + info.tile_size_y;
    d = player.x_m + info.tile_size_x;
	while (player.y_m < d2)
	{
        player.x_m = or_x;
		while (player.x_m < d)
		{
            if ((player.y_m == or_y || player.y_m == d2 - 1 || player.x_m == or_x || player.x_m == d - 1) && num == 1)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, color);
            else if (num == 1)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, color);
            else if ((player.y_m == or_y || player.y_m == d2 - 1 || player.x_m == or_x || player.x_m == d - 1) && num == 0)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, 0x0);
            else if (num == 0)
                put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, 0xffffff);
			player.x_m++;
		}
		player.y_m++;
	}
}

void    draw_rays(t_player player)
{
    int i;
    int r;
    int or_x;
    int or_y;

    i = 0;
    or_x = player.x_p;
    or_y = player.y_p;
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
}


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
}
