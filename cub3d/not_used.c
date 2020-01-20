#include "cube3d.h"

void put_square(t_player player, int color, int num)
{
    int d;
    int d2;
    int or_x;
    int or_y;

    or_y = player.y_m;
    or_x = player.x_m;
    d2 = player.y_m + TILE_SIZE;
    d = player.x_m + TILE_SIZE;
	while (player.y_m < d2)
	{
        player.x_m = or_x;
		while (player.x_m < d)
		{
            if ((player.y_m == or_y || player.y_m == d2 - 1 || player.x_m == or_x || player.x_m == d - 1) && num == 1)
            {
                if (player.y_m > 0 && player.y_m < info.win_height && player.x_m > 0 && player.x_m < info.win_width)
                    put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, color);
            }
            else if (num == 1)
            {
                if (player.y_m > 0 && player.y_m < info.win_height && player.x_m > 0 && player.x_m < info.win_width)
                    put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, color);
            }
            else if ((player.y_m == or_y || player.y_m == d2 - 1 || player.x_m == or_x || player.x_m == d - 1) && num == 0)
            {
                if (player.y_m > 0 && player.y_m < info.win_height && player.x_m > 0 && player.x_m < info.win_width)
                    put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, 0x0);
            }
            else if (num == 0)
                if (player.y_m > 0 && player.y_m < info.win_height && player.x_m > 0 && player.x_m < info.win_width)
                    put_pix(MINI_MAP * player.x_m, MINI_MAP * player.y_m, 0xffffff);
			player.x_m++;
		}
		player.y_m++;
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
        if (player.x_p >= 0 && player.x_p < info.win_x && player.y_p >= 0 && player.y_p < info.win_y)
		    put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, player.color);
		phi += 0.1;
	}
   
    // while (r < 60)
    // {
    //     put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, 0xff0000);
    //     player.x_p = or_x + (r * cos(player.direction * VAL));
    //     player.y_p = or_y + (r * sin(player.direction * VAL));
    //     r++;
    // }
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
            if (player.x_p >= 0 && player.x_p < info.win_x && player.y_p >= 0 && player.y_p < info.win_y)
                put_pix(MINI_MAP * player.x_p, MINI_MAP * player.y_p, player.color);
            r++;
        }
        i++;
    }
}