#include "cube3d.h"

void	put_pix(int x, int y, int color)
{
    if (x >= 0 && x < info.win_width && y >= 0 && y < info.win_height)
        info.img_data[x + (y * info.win_width)] = color;
}

void init_img()
{
    int bpp;
	int size_line;
	int endian;
    
    // mlx_destroy_image(info.mlx_ptr, info.img_ptr);
    // mlx_clear_window(info.mlx_ptr, info.win_ptr);
    info.img_ptr = mlx_new_image(info.mlx_ptr, info.win_width, info.win_height);
	info.img_data = (int *)mlx_get_data_addr(info.img_ptr, &bpp, &size_line, &endian);
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

int has_wall(float y, float x)
{
    if (y > 0 && y < info.win_height && x > 0 && x < info.win_width)
        return (map[(int)y / info.tile_size_y][(int)x / info.tile_size_x] != 0 && map[(int)y / info.tile_size_y][(int)x / info.tile_size_x] != 'N');
    return (1);
}

// FOR CASTING //

float dist_p(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
float normalize_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    angle += (angle < 0) ? TWO_PI : 0;
    return (angle);
}
int normalize_angle_deg(int angle)
{
    angle = angle % 360;
    angle += (angle < 0) ? 360 : 0;
    return (angle);
}